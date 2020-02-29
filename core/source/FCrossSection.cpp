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

FCrossSection::FCrossSection(std::vector<QVector2D> t_coordinates) {
	initialize(t_coordinates);
}

FGeometry* FCrossSection::toGeometry(float thickness) {
	FGeometry* geometry = new FGeometry();
	
	// find the offset for the new end face
	auto offset = DEPTH_NORMAL * thickness;

	// find new sizes for vertex, index and normal 
	// buffers
	size_t vs = vertices.size();
	size_t is = indices.size();

	vertices.resize(vs * 2);
	normals.resize(vs * 2);
	indices.resize(is * 2);

	// duplicate front-surface geometry along the
	// offset
	for (uint i = 0; i < vs; ++i) {
		uint j = i == vs - 1 ? 0 : i + 1;

		vertices[i + vs] = vertices[i] + offset;
			
		uint a = i,                 // first, original side
				b = j,                 // second, original side
				c = i + (uint)vs,      // first, far side
				d = j + (uint)vs;      // second, far side

		indices.insert(indices.end(), {
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

		indices[a] = indices[c - is] + k;
		indices[b] = indices[b - is] + k;
		indices[c] = indices[a - is] + k;
	}

	// calculate normals for each vertex of each
	// triangle in the mesh
	for (size_t j = 0; j < indices.size();) {
		auto a = indices[j++];
		auto b = indices[j++];
		auto c = indices[j++];
		auto n = QVector3D::crossProduct(
			vertices[b] - vertices[a],
			vertices[c] - vertices[a]
		);
		normals[a] += n;
		normals[b] += n;
		normals[c] += n;
	}

	geometry->setVertices(vertices);
	geometry->setNormals(normals);
	geometry->setIndices(indices);

	return geometry;
}