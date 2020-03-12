#include "FModelExtruded.h"

/*! \brief Constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FCrossSection* t_section, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_section->toGeometry(), t_transform, t_material)
	, section(t_section)
{
	renderer()->setPrimitiveType(QtRenderType::Triangles);
}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FCrossSection* t_section, QColor t_color)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(t_color))
{}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FCrossSection* t_section)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(RED))
{}

/*! \brief Set the extruded length
 */
void FModelExtruded::setLength(float t_length) {
	section->setLength(t_length);
	section->updateGeometry(geometry());
}

/*! \brief Get the extruded length
 */
float FModelExtruded::length() {
	return section->length();
}
