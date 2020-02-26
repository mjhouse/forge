#include <array>
#include <vector>

#include "Geometry.h"
#include "earcut.h"

std::vector<uint> Geometry::tessellate(std::vector<QVector3D> points) {
    std::vector<std::vector<std::array<double, 2>>> polygon{ {} };

    for (const auto& p : points) {
        polygon[0].push_back(std::array<double, 2>{p.x(), p.y()});
    }

    return mapbox::earcut<uint>(polygon);
}

void Geometry::setVertices(std::vector<QVector3D> t_vertices) {
    setVertexData(t_vertices);
    setVertexBuffer(this->buffer, t_vertices.size());
}

void Geometry::setNormals(std::vector<QVector3D> t_normals) {
    setNormalData(t_normals);
    setNormalBuffer(this->normals, t_normals.size());
}

void Geometry::setIndices(std::vector<uint> t_indices) {
    setIndexData(t_indices);
    setIndexBuffer(this->indices, t_indices.size());
}

std::vector<QVector3D> Geometry::getVertices() {
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

std::vector<QVector3D> Geometry::getNormals() {
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

std::vector<uint> Geometry::getIndices() {
    QByteArray data = this->indices->data();
    int count = data.size() / sizeof(uint);
    std::vector<uint> index(count);

    uint* raw = reinterpret_cast<uint*>(data.data());
    for (int i = 0; i < count; ++i) {
        index[i] = raw[i];
    }

    return index;
}


Geometry::Geometry(QNode* parent)
    : buffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, this))
    , normals(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, this))
    , indices(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, this))
    , posAttribute(nullptr)
    , normAttribute(nullptr)
    , idxAttribute(nullptr)
{

}

void Geometry::setVertexData(std::vector<QVector3D> vertices) {
    QByteArray data;

    // size the output bytearray and get direct access
    data.resize(vertices.size() * 3 * sizeof(float));
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

void Geometry::setNormalData(std::vector<QVector3D> normals) {
    QByteArray data;

    // size the output bytearray and get direct access
    data.resize(normals.size() * 3 * sizeof(float));
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

void Geometry::setIndexData(std::vector<uint> indices) {
    QByteArray data;
    data.resize(indices.size() * sizeof(uint));
    uint* raw = reinterpret_cast<uint*>(data.data());

    int i = 0;
    for (const uint& v : indices) {
        raw[i++] = v;
    }

    this->indices->setData(data);
}

void Geometry::setVertexBuffer(QtBuffer* buffer, uint count) {
    posAttribute = new QtAttribute();
    posAttribute->setAttributeType(QtAttribute::VertexAttribute);
    posAttribute->setBuffer(buffer);
    posAttribute->setDataType(QtAttribute::Float);
    posAttribute->setDataSize(3);
    posAttribute->setByteOffset(0);
    posAttribute->setByteStride(3*sizeof(float));
    posAttribute->setCount(count);
    posAttribute->setName(QtAttribute::defaultPositionAttributeName());
	addAttribute(posAttribute);
}

void Geometry::setNormalBuffer(QtBuffer* buffer, uint count) {
    normAttribute = new QtAttribute();
    normAttribute->setAttributeType(QtAttribute::VertexAttribute);
    normAttribute->setBuffer(buffer);
    normAttribute->setDataType(QtAttribute::Float);
    normAttribute->setDataSize(3);
    normAttribute->setByteOffset(0);
    normAttribute->setByteStride(3*sizeof(float));
    normAttribute->setCount(count);
    normAttribute->setName(QtAttribute::defaultNormalAttributeName());
	addAttribute(normAttribute);
}

void Geometry::setIndexBuffer(Qt3DRender::QBuffer* buffer, uint count) {
    idxAttribute = new QtAttribute();
    idxAttribute->setAttributeType(QtAttribute::IndexAttribute);
    idxAttribute->setBuffer(buffer);
    idxAttribute->setDataType(QtAttribute::UnsignedInt);
    idxAttribute->setDataSize(sizeof(uint));
    idxAttribute->setByteOffset(0);
    idxAttribute->setByteStride(0);
    idxAttribute->setCount(count);
	addAttribute(idxAttribute);
}

void Geometry::polygon() {
    // Vertices
    QVector3D v00(-1.0f, 1.0f, 0.0f);
    QVector3D v01(-1.0f, -1.0f, 0.0f);
    QVector3D v02(-0.5f, -1.0f, 0.0f);
    QVector3D v03(-0.5f, -0.5f, 0.0f);
    QVector3D v04(0.5f, -0.5f, 0.0f);
    QVector3D v05(0.5f, -1.0f, 0.0f);
    QVector3D v06(1.0f, -1.0f, 0.0f);
    QVector3D v07(1.0f, 1.0f, 0.0f);
    QVector3D v08(0.5f, 1.0f, 0.0f);
    QVector3D v09(0.5f, 0.5f, 0.0f);
    QVector3D v10(-0.5f, 0.5f, 0.0f);
    QVector3D v11(-0.5f, 1.0f, 0.0f);

    QVector3D n = QVector3D::normal(v03, v04, v09);

    std::vector<QVector3D> vertices = { v00, v01, v02, v03, v04, v05, v06, v07, v08, v09, v10, v11 };
    std::vector<QVector3D> normals = { n, n, n, n, n, n, n, n, n, n, n, n };
    std::vector<uint> indices = tessellate(vertices);

    this->setVertexData(vertices);
    this->setNormalData(normals);
    this->setIndexData(indices);

    this->setVertexBuffer(this->buffer, 12);
    this->setNormalBuffer(this->normals, 12);
    this->setIndexBuffer(this->indices, indices.size());
}

QtRenderer* Geometry::getRenderer(QtRenderType type) {
    auto renderer = new QtRenderer(this->parentNode());

    renderer->setInstanceCount(1);
    renderer->setFirstVertex(0);
    renderer->setFirstInstance(0);
    renderer->setPrimitiveType(type);
    renderer->setGeometry(this);

    return renderer;
}