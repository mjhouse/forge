#include "ForgeControl.h"
#include "ForgeWindow.h"
#include "ForgeApplication.h"

/* \brief Constructore
 */
ForgeControl::ForgeControl(ForgeWindow* t_parent, float t_x, float t_y)
	: m_title(new ForgeTitleBar(this))
	, m_body(new QWidget())
	, m_handle(m_title)
	, m_hasTitle(true)
	, m_anchor(0, 0)
	, m_initial(t_x, t_y)
	, m_parent(t_parent)
	, m_initialized(false)
	, m_persistent(false)
	, m_minimized(false)
	, m_unexposed(false)
{
	_subscribe(Channel::Action);
	
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
	auto layout = new QVBoxLayout();

	layout->setSpacing(0);
	layout->setMargin(0);

	layout->addWidget(m_title);
	layout->addWidget(m_body);

	this->setLayout(layout);
}

/* \brief Perform layout-related task after on show event
 */
void ForgeControl::showEvent(QShowEvent* t_event) {
	if (!m_initialized && m_parent != nullptr) {
		auto r = geometry();
		auto b = m_parent->geometry();

		m_anchor = QVector2D(
			b.width()  * m_initial.x() + r.width()  / 2, 
			b.height() * m_initial.y() + r.height() / 2);

		auto l = b.left() + b.width() * m_initial.x();
		auto t = b.top() + b.height() * m_initial.y();

		this->move(l, t);

		m_initialized = true;
		m_parent->addControl(this);
	}
}

/* \brief Moves the given child rect entirely 
 *		  inside the parent rect.
 */
QPoint ForgeControl::positionWithin(const QRect& t_parent, const QRect& t_child) {
	int t = t_parent.top();
	int r = t_parent.right();
	int b = t_parent.bottom();
	int l = t_parent.left();

	int cx = t_child.x();
	int cy = t_child.y();

	cx = std::min(std::max(cx, l), r - t_child.width());
	cy = std::min(std::max(cy, t), b - t_child.height());

	return QPoint(cx, cy);
}

/* \brief Snap this control to the new parent window.
 */
void ForgeControl::setControlled(ForgeWindow* t_parent) {
	if (m_parent)
		m_parent->removeControl(this);

	m_parent = t_parent;
	m_parent->addControl(this);

	auto rect = geometry();
	move(positionWithin(m_parent->geometry(), rect));
	findAnchor(rect);
}

/* \brief Find an anchor position inside of the 
 *		  current parent window.
 */
void ForgeControl::findAnchor(QRect& t_rect) {
	if (m_parent != nullptr) {
		auto pr = m_parent->geometry();
		auto cc = t_rect.center();

		auto l = cc.x() - pr.left();
		auto t = cc.y() - pr.top();

		m_anchor = QVector2D(l, t);
	}
}

/* \brief On move, try to find a new parent if this control
 *		  doesn't have one.
 */
void ForgeControl::moveEvent(QMoveEvent* t_event) {
	// look for a parent if this control is currently being
	// dragged.
	if (isMoving()) {
		auto rect = geometry();
		auto window = ForgeApplication::instance()->findWindow(rect.center());

		if (window == nullptr) {
			if (m_parent != nullptr) {
				m_parent->removeControl(this);
				m_parent = nullptr;
			}
		}
		else if (!window->is(m_parent)) {
			if (m_parent != nullptr) {
				m_parent->removeControl(this);
			}
			window->addControl(this);
			m_parent = window;
		}
		
		findAnchor(rect);
	}
}

/* \brief Handle keypress events for this control.
 */
void ForgeControl::keyPressEvent(QKeyEvent* t_event) {
	// escape closes dialogs by default- avoid this
	// by not sending the escape event to QDialog
	if (t_event->key() != Qt::Key_Escape) {
		QDialog::keyPressEvent(t_event);
	}
}

/* \brief If true, display a default title bar.
 */
void ForgeControl::hasTitle(bool t_title) {
	if (t_title && !m_hasTitle) {
		layout()->addWidget(m_title);
		m_hasTitle = true;
	}
	else if(!t_title && m_hasTitle) {
		layout()->removeWidget(m_title);
		m_hasTitle = false;
	}
}

/* \brief Set the title in the title bar.
 */
void ForgeControl::setTitle(QString t_title) {
	m_title->setTitle(t_title);
}

/* \brief Set a widget as the handle for this control.
 */
void ForgeControl::setHandle(FWidget* t_handle) {
	m_handle = t_handle;
}

/* \brief Set the central body widget.
 */
void ForgeControl::setCentralWidget(QWidget* t_widget) {
	layout()->replaceWidget(m_body, t_widget);
	delete m_body;
	m_body = t_widget;
}

/* \brief Get the current controlling parent.
 */
ForgeWindow* ForgeControl::controller() {
	return m_parent;
}

/* \brief If true, this control is being actively dragged.
 */
bool ForgeControl::isMoving() {
	return m_handle != nullptr &&
		m_handle->isDragging();
}

/* \brief If true, this control will be moved to a new 
 *		  window if the current parent window closes.
 */
bool ForgeControl::persistent() {
	return m_persistent;
}

/* \brief Set the persistent flag.
 */
void ForgeControl::setPersistent(bool t_persistent) {
	m_persistent = t_persistent;
}

/* \brief Get the current anchor within the parent window.
 */
QVector2D ForgeControl::anchor() {
	return m_anchor;
}

/* \brief set the current anchor within the parent window.
 */
void ForgeControl::setAnchor(QVector2D t_anchor) {
	m_anchor = t_anchor;
}

void ForgeControl::onMessage(Channel t_channel, UnknownMessage& t_message) {
	_route_in(t_channel, t_message, Channel::Action, Qt::ApplicationState, appStateChanged);
	_route_in(t_channel, t_message, Channel::Action, Qt::WindowState, winStateChanged);
}

/* \brief Handle application state changes (minimized etc.)
 */
void ForgeControl::appStateChanged(Message<Qt::ApplicationState>* t_state) {
	auto state = t_state->value();
	auto shown = isVisible();
	if ((state & Qt::ApplicationActive) == Qt::ApplicationActive) {
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
		if (shown) {
			hide();
			show();
		}
	}
	else if ((state & Qt::ApplicationInactive) == Qt::ApplicationInactive) {
		setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
		if (shown) {
			hide();
			show();
		}
	}
}

/* \brief Handle parent state changes.
 */
void ForgeControl::winStateChanged(Message<Qt::WindowState>* t_state) {

	if (m_parent == nullptr || !m_parent->isHandler(t_state->sender()))
		return;

	if ((t_state->value() & Qt::WindowMinimized) == Qt::WindowMinimized && isVisible()) {
		hide();
		m_minimized = true;
	}
	else if (m_minimized) {
		show();
		m_minimized = false;
	}
}