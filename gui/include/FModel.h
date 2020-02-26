#pragma once

#include "FGeometry.h"
#include "Defines.h"

class FModel : public QtEntity {
public:

	FGeometry* geometry;

	QtTransform* transform;

	QtRenderer* renderer;

	void initialize(QtComponent* material, QtTransform* transform) {
		renderer = geometry->getRenderer(QtRenderType::Points);

		this->addComponent(renderer);
		this->addComponent(material);
		this->addComponent(transform);
	}

public:

	FModel(QtEntity* parent, QtComponent* material)
		: QtEntity(parent)
		, geometry(new FGeometry(this))
		, transform(new QtTransform())
	{
		initialize(material,transform);
	}

	FModel(QtComponent* material)
		: geometry(new FGeometry(this))
		, transform(new QtTransform())
	{
		initialize(material, transform);
	}

	QVector3D getCentroid(std::vector<QVector3D> points) {
		float x = 0;
		float y = 0;
		float z = 0;
		int c = 0;

		auto r = transform->matrix();
		auto t = transform->translation();

		for (auto point : points) {
			auto p = QVector4D(point, 1) * r + t;
			x += p.x();
			y += p.y();
			z += p.z();
			c++;
		}

		return QVector3D(
			x / c, y / c, z / c);
	}

	QVector3D getCentroid() {
		auto points = geometry->getVertices();
		return getCentroid(points);
	}


};