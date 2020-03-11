#include "FModelLine.h"
#include "ForgeApplication.h"

FModelLine::FModelLine(FLine* t_section, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_section->toGeometry(), t_transform, t_material)
	, m_section(t_section)
{
	setSelectable(false);
	auto renderer = getRenderer();

	renderer->setPrimitiveType(QtRenderType::Lines);
}

FModelLine::FModelLine(FLine* t_section, QColor t_color)
	: FModelLine(t_section, new QtTransform(), new FMaterial(t_color))
{}

FModelLine::FModelLine(FLine* t_section)
	: FModelLine(t_section, new QtTransform(), new FMaterial(WHITE))
{}
