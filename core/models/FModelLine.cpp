#include "FModelLine.h"
#include "ForgeApplication.h"

/*! \brief Constructor for the line model
 */
FModelLine::FModelLine(FLine* t_section, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_section->toGeometry(), t_transform, t_material)
	, m_section(t_section)
{
	setSelectable(false);
	renderer()->setPrimitiveType(QtRenderType::Lines);
}

/*! \brief Secondary constructor for the line model
 */
FModelLine::FModelLine(FLine* t_section, QColor t_color)
	: FModelLine(t_section, new QtTransform(), new FMaterial(t_color, "vertex_shader", "line_shader"))
{}

/*! \brief Secondary constructor for the line model
 */
FModelLine::FModelLine(FLine* t_section)
	: FModelLine(t_section, new QtTransform(), new FMaterial(WHITE, "vertex_shader", "line_shader"))
{}

void FModelLine::setWidth(float t_width) {
	m_section->setWidth(t_width);
	m_section->updateGeometry(geometry());
}

float FModelLine::width() {
	return m_section->width();
}