#include "FLine.h"
#include "earcut.h"

#include <array>
#include <vector>

FLine::FLine(std::vector<QVector3D> t_coordinates)
{
	vertices = t_coordinates;
	indices = std::vector<uint>(t_coordinates.size());

	for (uint i = 0; i < t_coordinates.size(); i++)
	{
		indices[i] = i;
	}
}

FGeometry* FLine::toGeometry() {
	FGeometry* geometry = new FGeometry();
	updateGeometry(geometry);
	return geometry;
}

void FLine::updateGeometry(FGeometry* t_geometry) {

	auto nvertices = vertices;
	auto nindices  = indices;

	std::vector<QVector3D> normals;
	for (auto i : nindices) {
		normals.push_back(QVector3D(0,0,1));
	}
	

	t_geometry->setVertices(nvertices);
	t_geometry->setNormals(normals);
	t_geometry->setIndices(nindices);
}