#include "FCrossSection.h"
#include "earcut.h"
#include "exceptions.h"

#include <array>
#include <vector>

/*! \brief Initialize the surface given points defining a  
 *		   counter-clockwise border.
 */
void FCrossSection::initialize(std::vector<QVector3D>& t_coordinates) {
	size_t size = t_coordinates.size();

	m_vertices.clear();
	m_normals.clear();
	m_indices.clear();

	m_vertices.resize(size);
	m_normals.resize(size);

	m_vertices.assign(t_coordinates.begin(), 
					  t_coordinates.end());

	QVector3D n = QVector3D::normal(
		m_vertices[0],
		m_vertices[1],
		m_vertices[2]);

	for (int i = 0; i < size; ++i)
		m_normals[i] = n;

	// generate surface triangles
	tessellate();
}

/*! \brief Use the earcut algorithm in earcut.h to tessellate
 *		   the surface before initial thickening.
 */
void FCrossSection::tessellate() {
	std::vector<std::vector<std::array<double, 2>>> polygon{ {} };

	for (const auto& p : m_vertices) {
		polygon[0].push_back(std::array<double, 2>{p.x(), p.y()});
	}

	m_indices = mapbox::earcut<uint>(polygon);
}

/*! \brief The constructor takes counter-clockwise points defining
 *		   a 2D surface around a local origin.
 */
FCrossSection::FCrossSection() 
	: m_vertices()
	, m_normals()
	, m_indices()
	, m_length(DEPTH_LENGTH)
{}

/*! \brief Create a 3D FGeometry object from the crosssection
 *		   given a length.
 */
FGeometry* FCrossSection::toGeometry() {
	auto geometry = new FGeometry();
	updateGeometry(geometry);
	return geometry;
}

/*! \brief Create a 3D FGeometry object by performing a 
 *		   simple extrusion on the crosssection surface.
 */
void FCrossSection::updateGeometry(FGeometry* t_geometry) {
	check_null(t_geometry,"Geometry cannot be null");

	// find the offset for the new end face
	auto offset = DEPTH_NORMAL * (m_length * -1);

	auto nvertices = m_vertices;
	auto nnormals  = m_normals;
	auto nindices  = m_indices;

	// find new sizes for vertex, index and normal 
	// buffers
	size_t vs = nvertices.size();
	size_t is = nindices.size();

	nvertices.resize(vs * 2);
	nnormals.resize(vs * 2);
	nindices.resize(is * 2);

	// duplicate front-surface geometry along the
	// offset
	for (uint i = 0; i < vs; ++i) {
		uint j = i == vs - 1 ? 0 : i + 1;

		nvertices[i + vs] = nvertices[i] + offset;

		uint a = i,                 // first, original side
			b = j,                  // second, original side
			c = i + (uint)vs,       // first, far side
			d = j + (uint)vs;       // second, far side

		nindices.insert(nindices.end(), {
			a, c, d, d, b, a
			});
	}

	// duplicate existing triangle patterns with a 
	// reversed winding order (e.g  a,b,c => c,b,a)
	uint k = (uint)vs;
	for (int i = 0; i < is; i += 3) {
		auto a = i + is,
			b = a + 1,
			c = b + 1;

		nindices[a] = nindices[c - is] + k;
		nindices[b] = nindices[b - is] + k;
		nindices[c] = nindices[a - is] + k;
	}

	// calculate normals for each vertex of each
	// triangle in the mesh
	for (size_t j = 0; j < nindices.size();) {
		auto a = nindices[j++];
		auto b = nindices[j++];
		auto c = nindices[j++];
		auto n = QVector3D::crossProduct(
			nvertices[b] - nvertices[a],
			nvertices[c] - nvertices[a]
		);
		nnormals[a] += n;
		nnormals[b] += n;
		nnormals[c] += n;
	}

	t_geometry->setVertices(nvertices);
	t_geometry->setNormals(nnormals);
	t_geometry->setIndices(nindices);
}

void FCrossSection::setGeometry(std::vector<QVector3D>& t_points) {
	initialize(t_points);
}

/*! \brief Set the length.
 */
void FCrossSection::setLength(float t_length) {
	m_length = t_length;
}

/*! \brief Get the length.
 */
float FCrossSection::length() {
	return m_length;
}