#pragma once

#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QPickEvent>

#include <HasIdentifier.h>

#include "FDefaultMaterial.h"
#include "FCrossSection.h"
#include "FGeometry.h"
#include "Defines.h"

#include "FModel.h"

#define RED QColor::fromRgbF(1.0,0.3,0.3)

class FCrossSection;

	class FModelExtruded : public FModel {
	private:

		FCrossSection* section;

	public:

		FModelExtruded(FCrossSection* t_section, QtTransform* t_transform, FMaterial* t_material);

		FModelExtruded(FCrossSection* t_section, QColor t_color);

		FModelExtruded(FCrossSection* t_section);

		void setLength(float t_length);
	};
