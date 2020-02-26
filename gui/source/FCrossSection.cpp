#include "FCrossSection.h"

void FCrossSection::initialize(std::vector<QVector3D> points) {
	renderer->setPrimitiveType(QtRenderType::Triangles);

	size_t size = points.size();
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

		// duplicate geometry and flip the normals
		size_t vsize = vertices.size();
		size_t isize = indices.size();
		
		vertices.resize(vsize * 2);
		normals.resize(vsize * 2);
		indices.resize(isize * 2);

		for (int i = 0; i < vsize; ++i) {
			vertices[i + vsize] = vertices[i] + offset;
			normals[i + vsize] = normals[i];
			normals[i] = -normals[i];
		}
		
		// duplicate known triangle patterns
		for (int i = 0; i < isize; ++i) {
			indices[i + isize] = indices[i] + (uint)vsize;
		}

		// reverse the winding order of the triangles
		for (int i = 0; i < isize; i += 3) {
			std::swap(indices[i], indices[i + 2]);
		}

		auto centroid = getCentroid(vertices);
		for (int i = 0; i < vsize; ++i) {
			int j = i == vsize - 1 ? 0 : i + 1;

			// find two points that make up an edge on
			// the original end
			auto a = vertices[i];
			auto b = vertices[j];

			// find the duplicate points of the new end
			auto c = vertices[i + vsize];
			auto d = vertices[j + vsize];

			auto m = QVector3D(b - a).normalized();
			auto n = QVector3D::crossProduct(b - a, c - b).normalized();

			// find the "right" side of the direction of travel-
			// points are assumed to be counterclockwise around boundary
			QVector3D normal = n;
			if (m.x() * n.y() > n.x()* m.y()) {
				normal = -n;
			}

			indices.push_back(i);
			indices.push_back(j);
			indices.push_back(j + (uint)vsize);
			indices.push_back(j + (uint)vsize);
			indices.push_back(i + (uint)vsize);
			indices.push_back(i);

			//normals[i] += normal;
			//normals[j] += normal;
			//normals[i + vsize] += normal;
			//normals[j + vsize] += normal;
		}

		//for (int i = 0; i < normals.size(); ++i) {
		//	normals[i] = normals[i].normalized();
		//}

		geometry->setVertices(vertices);
		geometry->setNormals(normals);
		geometry->setIndices(indices);
	}
}