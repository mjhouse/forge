#pragma once

#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QPickEvent>

#include <HasIdentifier.h>

#include "FMaterial.h"
#include "FCrossSection.h"
#include "FGeometry.h"
#include "Defines.h"

#include "FModel.h"
#include "FLine.h"

#define RED   QColor::fromRgbF(1.0,0.3,0.3)
#define WHITE QColor::fromRgbF(1.0,1.0,1.0)

class FLine;

	class FModelLine : public FModel {
	private:
		
		FLine* m_section;

	public:

		FModelLine(FLine* t_section, QtTransform* t_transform, FMaterial* t_material);

		FModelLine(FLine* t_section, QColor t_color);

		FModelLine(FLine* t_section);
	};
