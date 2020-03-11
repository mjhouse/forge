#include "ForgeControl.h"
#include "ForgeWindow.h"
#include "ForgeApplication.h"

#define distance(p1,p2) std::sqrtf( std::powf(p2.x() - p1.x(),2) + std::pow(p2.y() - p1.y(),2))

ForgeControl::ForgeControl()
	: m_title(new ForgeTitleBar(this))
	, m_body(new QWidget())
	, m_handle(m_title)
	, m_hasTitle(true)
	, m_side(WindowSide::None)
	, m_anchor(0, 0)
	, m_parent(nullptr)
	, m_persistent(false)
{
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
	auto layout = new QVBoxLayout();

	layout->setSpacing(0);
	layout->setMargin(0);

	layout->addWidget(m_title);
	layout->addWidget(m_body);

	this->setLayout(layout);
	(void)this->connect(ForgeApplication::instance(), &QGuiApplication::applicationStateChanged,
						this, &ForgeControl::stateChanged);
}

QPoint ForgeControl::positionWithin(QRect& t_parent, QRect& t_child) {
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

void ForgeControl::moveEvent(QMoveEvent* t_event) {
	if (m_parent == nullptr || isMoving()) {
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

		findSide(rect);
	}
}

void ForgeControl::setControlled(ForgeWindow* t_parent) {
	if (m_parent)
		m_parent->removeControl(this);

	m_parent = t_parent;
	m_parent->addControl(this);

	auto rect = geometry();
	move(positionWithin(m_parent->geometry(), rect));
	findSide(rect);
}

void ForgeControl::findSide(QRect& t_rect) {
	if (m_parent != nullptr) {
		auto pr = m_parent->geometry();
		auto cc = t_rect.center();

		auto w = width();

		auto l = cc.x() - pr.left();
		auto t = cc.y() - pr.top();

		m_anchor = QVector2D(l, t);
	}
}

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

void ForgeControl::setTitle(QString t_title) {
	m_title->setTitle(t_title);
}

void ForgeControl::setHandle(FWidget* t_handle) {
	m_handle = t_handle;
}

void ForgeControl::setCentralWidget(QWidget* t_widget) {
	layout()->replaceWidget(m_body, t_widget);
	delete m_body;
	m_body = t_widget;
}

void ForgeControl::setPersistent(bool t_persistent) {
	m_persistent = t_persistent;
}

void ForgeControl::stateChanged(Qt::ApplicationState state) {
	auto shown = isVisible();
	if (state == Qt::ApplicationActive) {
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	}
	else {
		setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
	}
	if(shown) show();
}