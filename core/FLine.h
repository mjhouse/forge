#pragma once

#include <Qt3DCore/QEntity>      
#include <QtGui/QVector3D>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QMaterial>

#include "FMaterial.h"
#include "FGeometry.h"
#include "FModel.h"
#include "Defines.h"

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH 0.5

class FLine : public QWidget {
	Q_OBJECT

private:	
	std::vector<QVector3D> vertices;

	std::vector<uint> indices;

public:
	FLine(std::vector<QVector3D> t_coordinates);

	FGeometry* toGeometry();

	void updateGeometry(FGeometry* t_geometry);
};
