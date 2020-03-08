#include "ForgeControl.h"
#include "ForgeApplication.h"

ForgeControl::ForgeControl()
	: QDialog()
	, IsControl(this)
	, m_title(new ForgeTitleBar(this))
	, m_body(new QWidget())
	, m_handle(m_title)
	, m_hasTitle(true)
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

void ForgeControl::moveEvent(QMoveEvent* t_event) {
	if (!controlled() || (m_handle && m_handle->isDragging())) {
		findController();
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