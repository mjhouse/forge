#include "ForgeTitleBar.h"

ForgeTitleButton::ForgeTitleButton(QString t_icon) {
	setIcon(resources::icon(t_icon));
	setObjectName("TitleButton");
}

ForgeTitleBar::ForgeTitleBar(QWidget* t_parent)
	: FWidget(t_parent)
	, m_name(new QLabel(""))
{
	setDrag(true);
	setDragTarget(t_parent);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	layout->setSpacing(0);
	layout->setContentsMargins(5, 2, 5, 2);

	auto close = new ForgeTitleButton("close");

	(void)this->connect(close, &QPushButton::released,
		this, &ForgeTitleBar::closeControl);

	layout->addWidget(m_name);
	layout->addStretch(1);
	layout->addWidget(close);
	this->setLayout(layout);
	this->setMinimumWidth(100);

	this->setObjectName("TitleBar");
}

void ForgeTitleBar::closeControl() {
	auto p = (QDialog*)parent();
	if (p != nullptr)
		p->close();
}

void ForgeTitleBar::setTitle(QString t_title) {
	m_name->setText(t_title);
}