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
#define DEPTH_LENGTH -0.5

class FCrossSection : public QWidget {
	Q_OBJECT

private:
	
	std::vector<QVector3D> vertices;

	std::vector<QVector3D> normals;

	std::vector<uint> indices;

	void initialize(std::vector<QVector2D> t_coordinates);

	void tessellate();

public:
	FCrossSection(std::vector<QVector2D> t_coordinates);

	FGeometry* toGeometry(float thickness = DEPTH_LENGTH);

signals:
	void crossSectionChanged(FCrossSection* crossSection);

};











//class FCrossSection : public FModel {
//private:
//
//	void initialize(std::vector<QVector2D> coordinates);
//
//public:
//	
//	FMaterial* material;
//	
//	FCrossSection(QtEntity* parent, FMaterial* t_material, std::vector<QVector2D> coordinates)
//		: FModel(parent, t_material)
//		, material(t_material)
//	{
//		initialize(coordinates);
//	}
//
//	FCrossSection(FMaterial* t_material, std::vector<QVector2D> coordinates)
//		: FModel(t_material)
//		, material(t_material)
//	{
//		initialize(coordinates);
//	}
//
//	void thicken();
//};