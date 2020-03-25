#include "FLine.h"
#include "earcut.h"

#include <vector>
#include <cmath>
#include <array>

/*! \brief Constructor for the line.
 */
FLine::FLine(QVector3D t_start, QVector3D t_end)
	: m_width(1)
	, m_start(t_start)
	, m_end(t_end)
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
void FLine::updateGeometry(FGeometry* t_geometry) 
{
	std::vector<QVector3D> vertices = { m_start, m_end };
	std::vector<uint> indices  = { 0, 1 };
	
	t_geometry->setVertices(vertices);
	t_geometry->setIndices(indices);
}

void FLine::setWidth(float t_width) {
	m_width = t_width;
}

float FLine::width() {
	return m_width;
}