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

#define RED QColor::fromRgbF(1.0,0.3,0.3)

class FCrossSection;

	class FModel : public QtEntity, public components::HasIdentifier {
	private:

		FGeometry* geometry;

		QtTransform* transform;

		FMaterial* material;

		QtRenderer* renderer;

		bool selectable;

	public:

		FModel(FGeometry* t_section, QtTransform* t_transform, FMaterial* t_material);

		FModel(FGeometry* t_section, QColor t_color);

		FModel(FGeometry* t_section);

		FModel();

		QVector3D getCentroid(std::vector<QVector3D> points);

		QVector3D getCentroid();

		QtTransform* getTransform();

		bool isVisible();

		FGeometry* getGeometry();

		QtRenderer* getRenderer();

		void setSelectable(bool t_selectable);

		bool getSelectable();

		void unSelect();

		void select();

		void hide();

		void show();
	};
