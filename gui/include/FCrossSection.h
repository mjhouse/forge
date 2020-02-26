#pragma once

#include "FGeometry.h"
#include "FModel.h"
#include "Defines.h"

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH 0.1

class FCrossSection : public FModel {
private:

	void initialize(std::vector<QVector3D> points);

public:
	FCrossSection(QtEntity* parent, QtComponent* material, std::vector<QVector3D> points)
		: FModel(parent, material)
	{
		initialize(points);
	}

	FCrossSection(QtComponent* material, std::vector<QVector3D> points)
		: FModel(material)
	{
		initialize(points);
	}

	void thicken();
};