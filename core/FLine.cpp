#include "FLine.h"
#include <vector>

/*! \brief Constructor for the line.
 */
FLine::FLine(std::vector<QVector3D> t_coordinates)
	: m_vertices(t_coordinates)
	, m_indices(t_coordinates.size())
{
	for (auto i = 0; i < t_coordinates.size(); ++i) {
		m_indices[i] = i;
	}
}

/*! \brief Convert the line to an FGeometry object.
 */
FGeometry* FLine::toGeometry() {
	FGeometry* geometry = new FGeometry();
	updateGeometry(geometry);
	return geometry;
}

/*! \brief Update an existing FGeometry instance.
 */
void FLine::updateGeometry(FGeometry* t_geometry) 
{
	std::vector<QVector3D> normals;
	for (auto i : m_indices) {
		normals.push_back(QVector3D(0,0,1));
	}

	t_geometry->setVertices(m_vertices);
	t_geometry->setNormals(normals);
	t_geometry->setIndices(m_indices);
}