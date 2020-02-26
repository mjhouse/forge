#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <QtGui/QResizeEvent>

#include "MeshView.h"

MeshView::MeshView( int color ){
	defaultFrameGraph()->setClearColor(QColor(QRgb(color)));
	camera()->lens()->setPerspectiveProjection(45.0, 1, 0.1f, 1000.0);
	setRootEntity(new Qt3DCore::QEntity());
}

void MeshView::setRootEntity(Qt3DCore::QEntity* t_root) {
	auto camera = this->camera();

	camera->setPosition(QVector3D(0, 0, 10));
	camera->setUpVector(QVector3D(0, 1, 0));
	camera->setViewCenter(QVector3D(0, 0, 0));

	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(camera);
	light->setColor("white");
	light->setIntensity(1);
	camera->addComponent(light);

	auto controller = new Qt3DExtras::QOrbitCameraController(t_root);
	controller->setLinearSpeed(50.0f);
	controller->setLookSpeed(100.0f);
	controller->setCamera(camera);

	Qt3DWindow::setRootEntity(t_root);
	this->root = t_root;
}

Qt3DCore::QEntity* MeshView::rootEntity() {
	return root;
}

void MeshView::resizeEvent(QResizeEvent* e) {
	auto lens = camera()->lens();
	float aspectRatio = (float)width() / height();
	lens->setPerspectiveProjection(
		lens->fieldOfView(),
		aspectRatio, 
		lens->nearPlane(),
		lens->farPlane()
	);
}