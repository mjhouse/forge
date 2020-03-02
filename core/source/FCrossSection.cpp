#include "FCrossSection.h"
#include "earcut.h"

#include <array>
#include <vector>

void FCrossSection::initialize(std::vector<QVector2D> t_coordinates) {
	size_t size = t_coordinates.size();

	// convert coordinates to 3d points
	vertices.resize(size);
	for (size_t i = 0; i < size; ++i) {
		auto p = t_coordinates[i];
		vertices[i] = QVector3D(p.x(), p.y(), 0.0);
	}

	QVector3D n = QVector3D::normal(
		vertices[0],
		vertices[1],
		vertices[2]);

	normals.resize(size);
	for (int i = 0; i < size; ++i)
		normals[i] = n;

	// generate surface triangles
	tessellate();
}

void FCrossSection::tessellate() {
	std::vector<std::vector<std::array<double, 2>>> polygon{ {} };

	for (const auto& p : vertices) {
		polygon[0].push_back(std::array<double, 2>{p.x(), p.y()});
	}

	indices = mapbox::earcut<uint>(polygon);
}

FCrossSection::FCrossSection(std::vector<QVector2D> t_coordinates) 
	: length(DEPTH_LENGTH)
{
	initialize(t_coordinates);
}

FGeometry* FCrossSection::toGeometry() {
	FGeometry* geometry = new FGeometry();
	updateGeometry(geometry);
	return geometry;
}

void FCrossSection::updateGeometry(FGeometry* t_geometry) {
	// find the offset for the new end face
	auto offset = DEPTH_NORMAL * (length * -1);

	auto nvertices = vertices;
	auto nnormals  = normals;
	auto nindices  = indices;

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

void FCrossSection::setLength(float t_length) {
	length = t_length > 0 ? t_length : 0.1;
};