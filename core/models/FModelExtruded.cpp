#include "FModelExtruded.h"

/*! \brief Constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_symbol, QtTransform* t_transform, FMaterial* t_material)
	: FModel(t_symbol, t_transform, t_material)
	, m_section(t_symbol)
{
	renderer()->setPrimitiveType(QtRenderType::Triangles);
}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_symbol, QColor t_color)
	: FModelExtruded(t_symbol, new QtTransform(), new FMaterial(t_symbol,t_color))
{}

/*! \brief Secondary constructor for the extruded model
 */
FModelExtruded::FModelExtruded(FSymbol* t_symbol)
	: FModelExtruded(t_symbol, new QtTransform(), new FMaterial(t_symbol,RED))
{}

