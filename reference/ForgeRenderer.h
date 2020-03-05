#pragma once

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <QtGui/QResizeEvent>

#include "FModel.h"
#include "Defines.h"

class FModel;

class ForgeRenderer : public Qt3DWindow {
	Q_OBJECT

private:

	QtOrbitController* controller;

	QtEntity* root;

	QWidget* widget;

	ForgeRenderer();

	void resizeEvent(QResizeEvent* event);

	void mouseMoveEvent(QMouseEvent* e) override;

	void mousePressEvent(QMouseEvent* e) override;

	void mouseReleaseEvent(QMouseEvent* e) override;

public:
	
	static ForgeRenderer* instance();

	QWidget* getView();

	void setBackground(QRgb t_color);

	void addModel(FModel* t_model);

	QVector3D cameraPosition();
	
signals:
	void mouseMove(QMouseEvent* e);

	void mousePress(QMouseEvent* e);

	void mouseRelease(QMouseEvent* e);

};