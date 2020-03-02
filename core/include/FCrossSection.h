#pragma once

#include <Qt3DCore/QEntity>      
#include <QtGui/QVector2D>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QMaterial>

#include "FDefaultMaterial.h"
#include "FGeometry.h"
#include "FModel.h"
#include "Defines.h"

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH 0.5

class FCrossSection : public QWidget {
	Q_OBJECT

private:
	
	std::vector<QVector3D> vertices;

	std::vector<QVector3D> normals;

	std::vector<uint> indices;

	float length;

	void initialize(std::vector<QVector2D> t_coordinates);

	void tessellate();

public:
	FCrossSection(std::vector<QVector2D> t_coordinates);

	FGeometry* toGeometry();

	void updateGeometry(FGeometry* t_geometry);

	void setLength(float t_length);
};
