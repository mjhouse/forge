#include <array>
#include <vector>

#include "FGeometry.h"
#include "exceptions.h"

/*! \brief Sets buffer data given QVector3D vertex points.
 */
void FGeometry::setVertexData(std::vector<QVector3D>& t_vertices) {
    QByteArray data = toData(t_vertices);
    m_vertices->setData(data);
}

/*! \brief Sets buffer data given QVector3D normal points.
 */
void FGeometry::setNormalData(std::vector<QVector3D>& t_normals) {
    QByteArray data = toData(t_normals);
    m_normals->setData(data);
}

/*! \brief Sets buffer data given uint indices for the vertex buffer.
 */
void FGeometry::setIndexData(std::vector<uint>& t_indices) {
    QByteArray data;
    data.resize((uint)t_indices.size() * sizeof(uint));
    uint* raw = reinterpret_cast<uint*>(data.data());

    int i = 0;
    for (const uint& v : t_indices) {
        raw[i++] = v;
    }

    m_indices->setData(data);
}

/*! \brief Creates a vertex buffer attribute if none exists.
 */
void FGeometry::createVertexAttribute(QtBuffer* t_buffer, uint t_count) {
    if (m_vertexAttribute == nullptr) {
        check_null(t_buffer, "QBuffer parameter is null");
        m_vertexAttribute = new QtAttribute();
        m_vertexAttribute->setAttributeType(QtAttribute::VertexAttribute);
        m_vertexAttribute->setBuffer(t_buffer);
        m_vertexAttribute->setVertexBaseType(QtAttribute::Float);
        m_vertexAttribute->setVertexSize(3);
        m_vertexAttribute->setByteOffset(0);
        m_vertexAttribute->setByteStride(3 * sizeof(float));
        m_vertexAttribute->setCount(t_count);
        m_vertexAttribute->setName(QtAttribute::defaultPositionAttributeName());
        addAttribute(m_vertexAttribute);
    }
}

/*! \brief Creates a normal buffer attribute if none exists.
 */
void FGeometry::createNormalAttribute(QtBuffer* t_buffer, uint t_count) {
    if (m_normalAttribute == nullptr) {
        check_null(t_buffer, "QBuffer parameter is null");
        m_normalAttribute = new QtAttribute();
        m_normalAttribute->setAttributeType(QtAttribute::VertexAttribute);
        m_normalAttribute->setBuffer(t_buffer);
        m_normalAttribute->setVertexBaseType(QtAttribute::Float);
        m_normalAttribute->setVertexSize(3);
        m_normalAttribute->setByteOffset(0);
        m_normalAttribute->setByteStride(3 * sizeof(float));
        m_normalAttribute->setCount(t_count);
        m_normalAttribute->setName(QtAttribute::defaultNormalAttributeName());
        addAttribute(m_normalAttribute);
    }
}

/*! \brief Creates an index buffer attribute if none exists.
 */
void FGeometry::createIndexAttribute(Qt3DRender::QBuffer* t_buffer, uint t_count) {
    if (m_indexAttribute == nullptr) {
        check_null(t_buffer, "QBuffer parameter is null");
        m_indexAttribute = new QtAttribute();
        m_indexAttribute->setAttributeType(QtAttribute::IndexAttribute);
        m_indexAttribute->setBuffer(t_buffer);
        m_indexAttribute->setVertexBaseType(QtAttribute::UnsignedInt);
        m_indexAttribute->setVertexSize(1);
        m_indexAttribute->setByteOffset(0);
        m_indexAttribute->setByteStride(0);
        m_indexAttribute->setCount(t_count);
        addAttribute(m_indexAttribute);
    }
}

/*! \brief Constructor that initializes all values.
 */
FGeometry::FGeometry()
    : m_vertices(new QtBuffer(this))
    , m_normals(new QtBuffer(this))
    , m_indices(new QtBuffer(this))
    , m_vertexAttribute(nullptr)
    , m_normalAttribute(nullptr)
    , m_indexAttribute(nullptr)
{}

/*! \brief Creates or updates the vertex buffer.
 */
void FGeometry::setVertices(std::vector<QVector3D> t_vertices) {
    setVertexData(t_vertices);
    createVertexAttribute(m_vertices, (uint)t_vertices.size());
}

/*! \brief Creates or updates the normal buffer.
 */
void FGeometry::setNormals(std::vector<QVector3D> t_normals) {
    setNormalData(t_normals);
    createNormalAttribute(m_normals, (uint)t_normals.size());
}

/*! \brief Creates or updates the index buffer.
 */
void FGeometry::setIndices(std::vector<uint> t_indices) {
    setIndexData(t_indices);
    createIndexAttribute(m_indices, (uint)t_indices.size());
}

/*! \brief Converts flat buffer data into a vector of QVector3D objects.
 */
std::vector<QVector3D> FGeometry::getVertices() {
    QByteArray data = m_vertices->data();
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

/*! \brief Converts flat buffer data into a vector of QVector3D objects.
 */
std::vector<QVector3D> FGeometry::getNormals() {
    QByteArray data = m_normals->data();
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

/*! \brief Converts flat buffer data into a vector of uint indices.
 */
std::vector<uint> FGeometry::getIndices() {
    QByteArray data = m_indices->data();
    int count = data.size() / sizeof(uint);
    std::vector<uint> index(count);

    uint* raw = reinterpret_cast<uint*>(data.data());
    for (int i = 0; i < count; ++i) {
        index[i] = raw[i];
    }

    return index;
}

/*! \brief Creates and returns a configured Qt GeometryRenderer for
 *         for this Geometry instance.
 */
QtRenderer* FGeometry::getRenderer(QtRenderType t_type) {
    auto renderer = new QtRenderer();
    
    renderer->setInstanceCount(1);
    renderer->setFirstVertex(0);
    renderer->setFirstInstance(0);
    renderer->setPrimitiveType(t_type);
    renderer->setGeometry(this);

    return renderer;
}

/*! \brief Verifies that the geometry is planar (all points lie in a plane).
 */
bool FGeometry::isPlanar() {
    auto v = getVertices();
    if (v.size() <= 3) return true;

    auto normal = QVector3D::crossProduct(
        v[1] - v[0], v[2] - v[0]).normalized();

    for (auto it = v.begin() + 3; it != v.end(); ++it) {
        if (QVector3D::dotProduct(*it - v[0], normal) != 0)
            return false;
    }

    return true;
}