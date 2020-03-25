#ifndef __FMODELLINE_H__
#define __FMODELLINE_H__

#include "FMaterial.h"
#include "FModel.h"
#include "FLine.h"
#include "Defines.h"

#define WHITE QColor::fromRgbF(1.0,1.0,1.0)

class FModelLine : public FModel {
private:
		
	FLine* m_section;	/*!< The line symbol used to define this model */

public:

	FModelLine(FLine* t_section, QtTransform* t_transform, FMaterial* t_material);

	FModelLine(FLine* t_section, QColor t_color);

	FModelLine(FLine* t_section);

	void setWidth(float t_width);

	float width();

};

#endif // __FMODELLINE_H__