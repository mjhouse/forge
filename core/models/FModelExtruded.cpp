#include "FModelExtruded.h"

/*! \brief Constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_section, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_section, t_transform, t_material)
	, m_section(t_section)
{
	renderer()->setPrimitiveType(QtRenderType::Triangles);
}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_section, QColor t_color)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(t_color))
{}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_section)
	: FModelExtruded(t_section, new QtTransform(), new FMaterial(RED))
{}

