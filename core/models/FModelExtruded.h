#ifndef __FMODELEXTRUDED_H__
#define __FMODELEXTRUDED_H__

#include <Qt3DCore/QEntity>

#include "FCrossSection.h"
#include "FMaterial.h"
#include "Defines.h"

#include "FModel.h"

#define RED QColor::fromRgbF(1.0,0.3,0.3)

class FModelExtruded : public FModel {
private:

	FSymbol* m_section;		/*!< The crosssection that defines this extrusion */

public:

	FModelExtruded(FSymbol* t_section, QtTransform* t_transform, FMaterial* t_material);

	FModelExtruded(FSymbol* t_section, QColor t_color);

	FModelExtruded(FSymbol* t_section);

};

#endif // __FMODELEXTRUDED_H__