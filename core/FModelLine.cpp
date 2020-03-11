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
	: FModelLine(t_section, new QtTransform(), new FMaterial(t_color))
{}

/*! \brief Secondary constructor for the line model
 */
FModelLine::FModelLine(FLine* t_section)
	: FModelLine(t_section, new QtTransform(), new FMaterial(WHITE))
{}
