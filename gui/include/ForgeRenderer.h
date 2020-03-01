#pragma once

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <QtGui/QResizeEvent>
#include "Defines.h"

class ForgeRenderer : public Qt3DWindow {
	Q_OBJECT

private:

	QtOrbitController* controller;

	QtEntity* root;

	QWidget* widget;

	ForgeRenderer()
		: root(new QtEntity())
		, controller(nullptr)
	{
		this->camera()->lens()->setPerspectiveProjection(45.0, 1, 0.1f, 1000.0);
		this->setBackground(QRgb(0x000000));
		this->setRootEntity(root);

		auto camera = this->camera();

		camera->setPosition(QVector3D(0, 10, 0));
		camera->setUpVector(QVector3D(0, 0, 1));
		camera->setViewCenter(QVector3D(0, 0, 0));

		controller = new QtOrbitController(root);
		controller->setLinearSpeed(50.0f);
		controller->setLookSpeed(100.0f);
		controller->setCamera(camera);

		widget = QWidget::createWindowContainer(this);
	}

	void resizeEvent(QResizeEvent* event) {
		auto lens = camera()->lens();
		lens->setPerspectiveProjection(
			lens->fieldOfView(),
			(float)width() / height(),
			lens->nearPlane(),
			lens->farPlane()
		);
	}

	void mouseMoveEvent(QMouseEvent* e) override {
		emit mouseMove(e);
	}

	void mousePressEvent(QMouseEvent* e) override {
		emit mousePress(e);
	}

	void mouseReleaseEvent(QMouseEvent* e) override {
		emit mouseRelease(e);
	}

public:
	
	static ForgeRenderer* instance() {
		static auto renderer = new ForgeRenderer();
		return renderer;
	}

	QWidget* getView() {
		return widget;
	}

	void setBackground(QRgb t_color) {
		this->defaultFrameGraph()->setClearColor(QColor(t_color));
	}

	void addModel(FModel* t_model) {
		t_model->setParent(root);
	}

	QVector3D cameraPosition() {
		return camera()->position();
	}
	
signals:
	void mouseMove(QMouseEvent* e);

	void mousePress(QMouseEvent* e);

	void mouseRelease(QMouseEvent* e);

};