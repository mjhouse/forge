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
	setLength(0.5);
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
	setLength(0.5);
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

	if (m_vertices.size() == 2) {
		auto start = m_vertices[0];
		auto end   = m_vertices[1];
		auto pose  = (end - start).normalized() * length();
		m_vertices[1] = pose;
	}
	
	m_geometry->setVertices(m_vertices);
	m_geometry->setIndices(indices);
}

FSymbol* FLine::copy() {
	return new FLine(this);
}
/*! \brief Set the length.
 */
void FLine::setLength(float t_length) {
	FSymbol::setProperty("length", t_length);
}

/*! \brief Get the length.
 */
float FLine::length() {
	return FSymbol::property<float>("length");
}
