#pragma once

#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QGeometryRenderer>

#include "FDefaultMaterial.h"
#include "FGeometry.h"
#include "Defines.h"

#define RED QColor::fromRgbF(1.0,0.3,0.3)

class FModel : public QtEntity {
private:

	FGeometry* geometry;

	QtTransform* transform;
	
	FMaterial* material;

	QtRenderer* renderer;

public:
	
	FModel( FGeometry* t_geometry, QtTransform* t_transform, FMaterial* t_material )
		: geometry(t_geometry)
		, transform(t_transform)
		, material(t_material)
	{
		renderer = geometry->getRenderer(
			QtRenderType::Triangles);

		this->addComponent(renderer);
		this->addComponent(material);
		this->addComponent(transform);
	}

	FModel( FGeometry* t_geometry, QColor t_color)
		: FModel(t_geometry, new QtTransform(), new FDefaultMaterial(t_color))
	{}

	FModel( FGeometry* t_geometry)
		: FModel(t_geometry, new QtTransform(), new FDefaultMaterial(RED))
	{}
	
	QVector3D getCentroid(std::vector<QVector3D> points);

	QVector3D getCentroid();

	QtTransform* getTransform() {
		return transform;
	}

};