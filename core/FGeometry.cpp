#include <array>
#include <vector>

#include "FGeometry.h"
#include "earcut.h"

std::vector<uint> FGeometry::tessellate(std::vector<QVector3D> points) {
    std::vector<std::vector<std::array<double, 2>>> polygon{ {} };

    for (const auto& p : points) {
        polygon[0].push_back(std::array<double, 2>{p.x(), p.y()});
    }

    return mapbox::earcut<uint>(polygon);
}

void FGeometry::setVertices(std::vector<QVector3D> t_vertices) {
    setVertexData(t_vertices);
    setVertexBuffer(this->buffer, (uint)t_vertices.size());
}

void FGeometry::setNormals(std::vector<QVector3D> t_normals) {
    setNormalData(t_normals);
    setNormalBuffer(this->normals, (uint)t_normals.size());
}

void FGeometry::setIndices(std::vector<uint> t_indices) {
    setIndexData(t_indices);
    setIndexBuffer(this->indices, (uint)t_indices.size());
}

std::vector<QVector3D> FGeometry::getVertices() {
    QByteArray data = this->buffer->data();
    std::vector<QVector3D> points;

    int count = data.size() / sizeof(float);
    if (count % 3 != 0) return points;

    float* raw = reinterpret_cast<float*>(data.data());
    for (int i = 0; i < count;) {
        float x = raw[i++];
        float y = raw[i++];
        float z = raw[i++];
        points.push_back(QVector3D(x, y, z));
    }

    return points;
}

std::vector<QVector3D> FGeometry::getNormals() {
    QByteArray data = this->normals->data();
    std::vector<QVector3D> points;

    int count = data.size() / sizeof(float);
    if (count % 3 != 0) return points;

    float* raw = reinterpret_cast<float*>(data.data());
    for (int i = 0; i < count;) {
        float x = raw[i++];
        float y = raw[i++];
        float z = raw[i++];
        points.push_back(QVector3D(x, y, z));
    }
    
    return points;
}

std::vector<uint> FGeometry::getIndices() {
    QByteArray data = this->indices->data();
    int count = data.size() / sizeof(uint);
    std::vector<uint> index(count);

    uint* raw = reinterpret_cast<uint*>(data.data());
    for (int i = 0; i < count; ++i) {
        index[i] = raw[i];
    }

    return index;
}

FGeometry::FGeometry()
    : buffer(new QtBuffer(this))
    , normals(new QtBuffer(this))
    , indices(new QtBuffer(this))
    , posAttribute(nullptr)
    , normAttribute(nullptr)
    , idxAttribute(nullptr)
{

}

void FGeometry::setVertexData(std::vector<QVector3D> vertices) {
    QByteArray data;

    // size the output bytearray and get direct access
    data.resize((uint)vertices.size() * 3 * sizeof(float));
    float* raw = reinterpret_cast<float*>(data.data());

    // transfer data from vertices to the raw array
    int idx = 0;
    for (const QVector3D& vertex : vertices) {
        raw[idx++] = vertex.x();
        raw[idx++] = vertex.y();
        raw[idx++] = vertex.z();
    }

    this->buffer->setData(data);
}

void FGeometry::setNormalData(std::vector<QVector3D> normals) {
    QByteArray data;

    // size the output bytearray and get direct access
    data.resize((uint)normals.size() * 3 * sizeof(float));
    float* raw = reinterpret_cast<float*>(data.data());

    // transfer data from vertices to the raw array
    int idx = 0;
    for (const QVector3D& vertex : normals) {
        raw[idx++] = vertex.x();
        raw[idx++] = vertex.y();
        raw[idx++] = vertex.z();
    }

    this->normals->setData(data);
}

void FGeometry::setIndexData(std::vector<uint> indices) {
    QByteArray data;
    data.resize((uint)indices.size() * sizeof(uint));
    uint* raw = reinterpret_cast<uint*>(data.data());

    int i = 0;
    for (const uint& v : indices) {
        raw[i++] = v;
    }

    this->indices->setData(data);
}

void FGeometry::setVertexBuffer(QtBuffer* buffer, uint count) {
    posAttribute = new QtAttribute();
    posAttribute->setAttributeType(QtAttribute::VertexAttribute);
    posAttribute->setBuffer(buffer);
    posAttribute->setVertexBaseType(QtAttribute::Float);
    posAttribute->setVertexSize(3);
    posAttribute->setByteOffset(0);
    posAttribute->setByteStride(3*sizeof(float));
    posAttribute->setCount(count);
    posAttribute->setName(QtAttribute::defaultPositionAttributeName());
	addAttribute(posAttribute);
}

void FGeometry::setNormalBuffer(QtBuffer* buffer, uint count) {
    normAttribute = new QtAttribute();
    normAttribute->setAttributeType(QtAttribute::VertexAttribute);
    normAttribute->setBuffer(buffer);
    normAttribute->setVertexBaseType(QtAttribute::Float);
    normAttribute->setVertexSize(3);
    normAttribute->setByteOffset(0);
    normAttribute->setByteStride(3*sizeof(float));
    normAttribute->setCount(count);
    normAttribute->setName(QtAttribute::defaultNormalAttributeName());
	addAttribute(normAttribute);
}

void FGeometry::setIndexBuffer(Qt3DRender::QBuffer* buffer, uint count) {
    idxAttribute = new QtAttribute();
    idxAttribute->setAttributeType(QtAttribute::IndexAttribute);
    idxAttribute->setBuffer(buffer);
    idxAttribute->setVertexBaseType(QtAttribute::UnsignedInt);
    idxAttribute->setVertexSize(1);
    idxAttribute->setByteOffset(0);
    idxAttribute->setByteStride(0);
    idxAttribute->setCount(count);
	addAttribute(idxAttribute);
}

QtRenderer* FGeometry::getRenderer(QtRenderType type) {
    auto renderer = new QtRenderer(this->parentNode());
    
    renderer->setInstanceCount(1);
    renderer->setFirstVertex(0);
    renderer->setFirstInstance(0);
    renderer->setPrimitiveType(type);
    renderer->setGeometry(this);

    return renderer;
}