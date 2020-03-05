#include "ForgeControl.h"
#include "ForgeApplication.h"

ForgeControl::ForgeControl()
	: QDialog()
	, m_title(new ForgeTitleBar(this))
	, m_body(new QWidget())
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

void ForgeControl::hasTitle(bool t_title) {
	if (t_title) {
		layout()->addWidget(m_title);
	}
	else {
		layout()->removeWidget(m_title);
	}
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