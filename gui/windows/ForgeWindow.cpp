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
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QScreenRayCaster>

#include "ForgeApplication.h"
#include "ForgeWindow.h"
#include "ForgeControl.h"
#include "exceptions.h"
#include "Defines.h"
#include "EventFilters.h"
#include "Config.h"

#define BLACK 0x000000
#define GRAY  0x212121

/*! \brief Constructor for ForgeWindow
 */
ForgeWindow::ForgeWindow()
	: m_camera(new QtCamera())
	, m_renderer(new QtForwardRenderer())
	, m_controls()
	, m_context(nullptr)
{
	// route events to channels
	_event_publish(ForgeWindow::windowStateChanged, Channel::Action);

	// subscribe to channels
	_subscribe(Channel::Action);

	this->setSurfaceType(QWindow::OpenGLSurface);
	this->resize(1024, 768);
	this->create();

	this->m_context = new QOpenGLContext;
	this->m_context->create();

	setMinimumHeight(100);
	setMinimumWidth(100);

	m_camera->lens()->setPerspectiveProjection(
		45.0, (float)1024/768, 0.1f, 1000.0);
	
	m_camera->setPosition(QVector3D(0, 10, 0));
	m_camera->setUpVector(QVector3D(0, 0, 1));
	m_camera->setViewCenter(QVector3D(0, 0, 0));
	
	m_renderer->setCamera(m_camera);
	m_renderer->setSurface(this);
	m_renderer->setClearColor(GRAY);
	
	this->installEventFilter(new CloseEventFilter(this,Channel::Action));
	this->installEventFilter(new ClickEventFilter(this,Channel::Action));

	m_context->makeCurrent(this);
	initializeOpenGLFunctions();
}

/*! \brief Destructor for ForgeWindow
 */
ForgeWindow::~ForgeWindow() {}

/*! \brief Adjusts perspective and resizes children.
 */
void ForgeWindow::resizeEvent(QResizeEvent* event) {
	auto lens = m_camera->lens();
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

/*! \brief Resizes children on move.
 */
void ForgeWindow::moveEvent(QMoveEvent* t_event) {
	auto s = size();
	QRect oldRect(t_event->oldPos(), s);
	QRect newRect(t_event->pos(), s);
	updateControls(oldRect, newRect);
}

/*! \brief Finds all current children and moves them to appropriate
 *		   anchor points when the window is resized or moved.
 */
void ForgeWindow::updateControls(QRect& oldRect, QRect& newRect) {
	auto cx = (float)newRect.width() / oldRect.width();
	auto cy = (float)newRect.height() / oldRect.height();
	
	for (auto control : m_controls.priority()) {
		auto c = control->geometry();
		auto a = control->anchor();

		auto w = c.width();
		auto h = c.height();

		// scale the anchor values to the new size
		a.setX(a.x() * cx);
		a.setY(a.y() * cy);

		// find top-left point of the control 
		// relative to the window
		float x = a.x() + newRect.x() - (w / 2);
		float y = a.y() + newRect.y() - (h / 2);

		// find current bounds of the window
		float l = newRect.x();
		float t = newRect.y();
		float r = l + newRect.width();
		float b = t + newRect.height();

		// move the new position to be inside the
		// window bounds.
		x = std::min(std::max(x, l), r - w);
		y = std::min(std::max(y, t), b - h);

		control->setAnchor(a);
		control->move(x, y);
	}
}

/*! \brief Sets the framegraph source for this window.
 */
void ForgeWindow::setRenderSource(QtFrameGraphNode* t_framegraph) {
	m_renderer->setParent(t_framegraph);
}

/*! \brief Sets the entity root for this window.
 */
void ForgeWindow::setRoot(QtEntity* t_root) {
	m_camera->setParent(t_root);
}

/*! \brief Removes the framegraph and entity parents.
 */
void ForgeWindow::clearParent() {
	m_renderer->setParent((QtFrameGraphNode*)nullptr);
	m_camera->setParent((QtEntity*)nullptr);
}

/*! \brief Get the camera for this window.
 */
QtCamera* ForgeWindow::camera() { 
	return m_camera; 
}

/*! \brief Get the renderer for this window.
 */
QtForwardRenderer* ForgeWindow::renderer() {
	return m_renderer;
}

/*! \brief Add a new child control.
 */
void ForgeWindow::addControl(ForgeControl* t_control) {
	if (t_control != nullptr && !m_controls.contains(t_control)) {
		m_controls.add(t_control);
	}
}

/*! \brief Remove an existing child control.
 */
void ForgeWindow::removeControl(ForgeControl* t_control) {
	if (t_control != nullptr && m_controls.contains(t_control)) {
		m_controls.remove(t_control);
	}
}

void ForgeWindow::onMessage(Channel t_channel, UnknownMessage& t_message) {
	_route_in(t_channel, t_message, Channel::Action, QCloseEvent*, onWindowClose);
}

/*! \brief Close or reassign child controls on close.
 */
void ForgeWindow::onWindowClose(Message<QCloseEvent*>* t_message) {
	auto window = (ForgeWindow*)t_message->sender();
	if (window->is(this)) {
		for (auto child : m_controls.priority()) {
			if (!child->persistent()) {
				child->close();
			}
			else {
				_publish(Channel::Reassign, child);
			}
		}
	}
}