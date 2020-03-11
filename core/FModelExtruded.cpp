#include "FModelExtruded.h"
#include "ForgeApplication.h"

FModelExtruded::FModelExtruded(FCrossSection* t_section, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_section->toGeometry(), t_transform, t_material)
	, section(t_section)
{
	auto renderer = getRenderer();
	renderer->setPrimitiveType(QtRenderType::Triangles);
}

FModelExtruded::FModelExtruded(FCrossSection* t_section, QColor t_color)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(t_color))
{}

FModelExtruded::FModelExtruded(FCrossSection* t_section)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(RED))
{}


void FModelExtruded::setLength(float t_length) {
	section->setLength(t_length);
	section->updateGeometry(getGeometry());
}

float FModelExtruded::length() {
	return section->length();
}
