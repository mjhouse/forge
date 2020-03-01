#include "ForgeRenderer.h"

ForgeRenderer::ForgeRenderer()
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

void ForgeRenderer::resizeEvent(QResizeEvent* event) {
	auto lens = camera()->lens();
	lens->setPerspectiveProjection(
		lens->fieldOfView(),
		(float)width() / height(),
		lens->nearPlane(),
		lens->farPlane()
	);
}

void ForgeRenderer::mouseMoveEvent(QMouseEvent* e) {
	emit mouseMove(e);
}

void ForgeRenderer::mousePressEvent(QMouseEvent* e) {
	emit mousePress(e);
}

void ForgeRenderer::mouseReleaseEvent(QMouseEvent* e) {
	emit mouseRelease(e);
}

ForgeRenderer* ForgeRenderer::instance() {
	static auto renderer = new ForgeRenderer();
	return renderer;
}

QWidget* ForgeRenderer::getView() {
	return widget;
}

void ForgeRenderer::setBackground(QRgb t_color) {
	this->defaultFrameGraph()->setClearColor(QColor(t_color));
}

void ForgeRenderer::addModel(FModel* t_model) {
	t_model->setParent(root);
}

QVector3D ForgeRenderer::cameraPosition() {
	return camera()->position();
}