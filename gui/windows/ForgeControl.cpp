#include "ForgeControl.h"
#include "ForgeWindow.h"
#include "ForgeApplication.h"

ForgeControl::ForgeControl()
	: QDialog()
	, m_parent(nullptr)
	, m_title(new ForgeTitleBar(this))
	, m_body(new QWidget())
	, m_handle(m_title)
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

void ForgeControl::findParent(QPoint t_point) {
	auto parent = ForgeApplication::instance()->findWindow(t_point);
	
	if (parent) {
		if (m_parent) 
			m_parent->removeControl(this);
		
		parent->addControl(this);
		m_parent = parent;
	}
	else {
		if(m_parent)
			m_parent->removeControl(this);
		m_parent = nullptr;
	}
}

void ForgeControl::moveEvent(QMoveEvent* t_event) {
	if (m_parent == nullptr || (m_handle && m_handle->isDragging())) {
		findParent(this->geometry().center());
	}
}

void ForgeControl::hasTitle(bool t_title) {
	if (t_title) {
		layout()->addWidget(m_title);
	}
	else {
		layout()->removeWidget(m_title);
	}
}

void ForgeControl::setHandle(FWidget* t_handle) {
	m_handle = t_handle;
}

void ForgeControl::setCentralWidget(QWidget* t_widget) {
	layout()->replaceWidget(m_body, t_widget);
	delete m_body;
	m_body = t_widget;
}

void ForgeControl::stateChanged(Qt::ApplicationState state) {
	if (state == Qt::ApplicationActive) {
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	}
	else {
		setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
	}
	show();
}