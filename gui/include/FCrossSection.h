#pragma once

#include <QtGui/QVector2D>

#include "FGeometry.h"
#include "FModel.h"
#include "Defines.h"

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH -0.5

class FCrossSection : public FModel {
private:

	void initialize(std::vector<QVector2D> coordinates);

public:
	FCrossSection(QtEntity* parent, QtComponent* material, std::vector<QVector2D> coordinates)
		: FModel(parent, material)
	{
		initialize(coordinates);
	}

	FCrossSection(QtComponent* material, std::vector<QVector2D> coordinates)
		: FModel(material)
	{
		initialize(coordinates);
	}

	void thicken();
};