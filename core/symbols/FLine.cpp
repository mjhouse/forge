#include "FLine.h"
#include "earcut.h"

#include <vector>
#include <cmath>
#include <array>

/*! \brief Constructor for the line.
 */
FLine::FLine()
	: m_vertices()
{}

/*! \brief Constructor for the line.
 */
FLine::FLine(QVector3D t_start, QVector3D t_end)
	: m_vertices({t_start,t_end})
{}

/*! \brief Convert the line to an FGeometry object.
 */
FGeometry* FLine::toGeometry() {
	FGeometry* geometry = new FGeometry();
	updateGeometry(geometry);
	return geometry;
}

/*! \brief Update an existing FGeometry instance.
 */
void FLine::updateGeometry(FGeometry* t_geometry) {
	std::vector<uint> indices(m_vertices.size());
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		indices[i] = (uint)i;
	}
	
	t_geometry->setVertices(m_vertices);
	t_geometry->setIndices(indices);
}

void FLine::setGeometry(std::vector<QVector3D>& t_points) {
	m_vertices.clear();
	m_vertices.resize(t_points.size());
	m_vertices.assign(t_points.begin(), t_points.end());
}