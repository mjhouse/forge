#include "FLine.h"
#include "earcut.h"

#include <vector>
#include <cmath>
#include <array>

/*! \brief Constructor for the line.
 */
FLine::FLine()
	: m_vertices()
	, m_geometry(new FGeometry())
{
	m_geometry->setRenderType(QtRenderType::Lines);
}

FLine::FLine(FLine* t_other)
	: FSymbol(t_other)
	, m_vertices(t_other->m_vertices)
	, m_geometry(new FGeometry())
{
	m_geometry->setRenderType(QtRenderType::Lines);
	updateGeometry();
}

/*! \brief Constructor for the line.
 */
FLine::FLine(QVector3D t_start, QVector3D t_end)
	: m_vertices({t_start,t_end})
	, m_geometry(new FGeometry())
{
	m_geometry->setRenderType(QtRenderType::Lines);
}

void FLine::setGeometry(std::vector<QVector3D>& t_points) {
	m_vertices.clear();
	m_vertices.resize(t_points.size());
	m_vertices.assign(t_points.begin(), t_points.end());
}

/*! \brief Convert the line to an FGeometry object.
 */
FGeometry* FLine::toGeometry() {
	updateGeometry();
	return m_geometry;
}

/*! \brief Update an existing FGeometry instance.
 */
void FLine::updateGeometry() {
	std::vector<uint> indices(m_vertices.size());
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		indices[i] = (uint)i;
	}
	
	m_geometry->setVertices(m_vertices);
	m_geometry->setIndices(indices);
}
