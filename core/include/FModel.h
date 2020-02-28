#pragma once

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QGeometryRenderer>

#include "FDefaultMaterial.h"
#include "FGeometry.h"
#include "Defines.h"

class FModel : public QtEntity {
public:

	FGeometry* geometry;

	QtTransform* transform;

	QtRenderer* renderer;

	void initialize(FMaterial* material, QtTransform* transform) {
		renderer = geometry->getRenderer(QtRenderType::Points);
		this->addComponent(renderer);
		this->addComponent(material);
		this->addComponent(transform);
	}

public:

	FModel(QtEntity* parent, FMaterial* material)
		: QtEntity(parent)
		, geometry(new FGeometry(this))
		, transform(new QtTransform())
	{
		initialize(material,transform);
	}

	FModel(FMaterial* material)
		: QEntity()
		, geometry(new FGeometry(this))
		, transform(new QtTransform())
	{
		initialize(material, transform);
	}

	QVector3D getCentroid(std::vector<QVector3D> points);

	QVector3D getCentroid();


};