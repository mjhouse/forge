#include "FCrossSection.h"

void FCrossSection::initialize(std::vector<QVector2D> coordinates) {
	renderer->setPrimitiveType(QtRenderType::Triangles);
	size_t size = coordinates.size();
	
	// convert coordinates to 3d points
	std::vector<QVector3D> points(size);
	for (size_t i = 0; i < size; ++i) {
		auto p = coordinates[i];
		points[i] = QVector3D(p.x(),p.y(),0.0);
	}
	
	QVector3D n = QVector3D::normal(
		points[0],
		points[1],
		points[2]);

	std::vector<QVector3D> normals(size);
	for (int i = 0; i < size; ++i)
		normals[i] = n;

	std::vector<uint> indices = geometry->tessellate(points);

	geometry->setVertices(points);
	geometry->setNormals(normals);
	geometry->setIndices(indices);

	assert(geometry->isPlanar());
}

void FCrossSection::thicken() {
	if (geometry->isPlanar()) {
		auto vertices = geometry->getVertices();
		auto normals = geometry->getNormals();
		auto indices = geometry->getIndices();

		// find the offset for the new end face
		auto offset = DEPTH_NORMAL * DEPTH_LENGTH;

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
	}
}