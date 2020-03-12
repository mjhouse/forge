#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QDockWidget>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QLineWidth>

#include "ForgeApplication.h"
#include "ForgeWindow.h"
#include "ForgeControl.h"
#include "Defines.h"
#include "Config.h"

#define BLACK 0x000000
#define GRAY  0x212121

bool CloseEventFilter::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::Close) {
		auto window = (ForgeWindow*)obj;
		emit window->onClose(window);
	}

	return QObject::eventFilter(obj, event);
}

bool StateEventFilter::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::WindowStateChange){
		auto window = (ForgeWindow*)obj;
		window->changeEvent((QWindowStateChangeEvent*)event);
	}

	return QObject::eventFilter(obj, event);
}

ForgeWindow::ForgeWindow()
	: camera(new QtCamera())
	, renderer(new QtForwardRenderer())
{

	this->setSurfaceType(QWindow::OpenGLSurface);
	this->resize(1024, 768);

	setMinimumHeight(100);
	setMinimumWidth(100);

	camera->lens()->setPerspectiveProjection(45.0, (float)1024/768, 0.1f, 1000.0);
	camera->setPosition(QVector3D(0, 10, 0));
	camera->setUpVector(QVector3D(0, 0, 1));
	camera->setViewCenter(QVector3D(0, 0, 0));

	renderer->setCamera(camera);
	renderer->setSurface(this);
	renderer->setClearColor(GRAY);

	this->installEventFilter(new CloseEventFilter(this));
	this->installEventFilter(new StateEventFilter(this));

	(void)this->connect(this, &ForgeWindow::onClose, this, &ForgeWindow::closing);
}

ForgeWindow::~ForgeWindow() {}

void ForgeWindow::updateControls(QRect& oldRect, QRect& newRect) {
	auto cx = (float)newRect.width() / oldRect.width();
	auto cy = (float)newRect.height() / oldRect.height();

	auto controls = m_controls.priority();

	for (auto control : controls) {
		auto cr = control->geometry();
		auto a = control->anchor();

		// scale the anchor values to the new size
		a.setX(a.x() * cx);
		a.setY(a.y() * cy);

		float x = a.x() + newRect.x() - (cr.width() / 2);
		float y = a.y() + newRect.y() - (cr.height() / 2);

		float l = newRect.x();
		float t = newRect.y();
		float r = l + newRect.width();
		float b = t + newRect.height();

		x = std::min(std::max(x, l), r - cr.width());
		y = std::min(std::max(y, t), b - cr.height());

		control->setAnchor(a);
		control->move(x, y);
	}
}

void ForgeWindow::setRenderSource(QtFrameGraphNode* t_framegraph) {
	renderer->setParent(t_framegraph);
}

void ForgeWindow::setRoot(QtEntity* t_root) {
	camera->setParent(t_root);
}

void ForgeWindow::focusInEvent(QFocusEvent* ev) {
	emit onFocus(this);
}

void ForgeWindow::resizeEvent(QResizeEvent* event) {
	auto lens = camera->lens();
	lens->setPerspectiveProjection(
		lens->fieldOfView(),
		(float)width() / height(),
		lens->nearPlane(),
		lens->farPlane()
	);

	auto rect = geometry();
	QRect oldRect(rect.topLeft(), event->oldSize());
	QRect newRect(rect.topLeft(), size());
	updateControls(oldRect, newRect);
}

void ForgeWindow::clearParent() {
	renderer->setParent((QtFrameGraphNode*)nullptr);
	camera->setParent((QtEntity*)nullptr);
}

QtCamera* ForgeWindow::getCamera() { 
	return camera; 
}

void ForgeWindow::moveEvent(QMoveEvent* t_event) {
	QRect oldRect(t_event->oldPos(), size());
	QRect newRect(t_event->pos(), size());
	updateControls(oldRect,newRect);
}

void ForgeWindow::changeEvent(QWindowStateChangeEvent* t_event) {
	if (t_event->oldState().testFlag(Qt::WindowMinimized) ||
	   (t_event->oldState().testFlag(Qt::WindowNoState)   &&
		this->windowState() == Qt::WindowMaximized))
	{
		//updateControls();
	}
}

void ForgeWindow::closing(ForgeWindow* t_window) {
	for (auto child : m_controls.priority()) {
		if (!child->persistent()) {
			child->close();
		}
		else {
			ForgeApplication::instance()
				->reassign(this,child);
		}
	}
}

void ForgeWindow::show() {
	QWindow::show();
	ForgeApplication::processEvents();
	emit onShow(this);
}

void ForgeWindow::addControl(ForgeControl* t_control) {
	m_controls.add(t_control);
}

void ForgeWindow::removeControl(ForgeControl* t_control) {
	m_controls.remove(t_control);
}
