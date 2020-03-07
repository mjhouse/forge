#include "ForgeTitleBar.h"

ForgeTitleButton::ForgeTitleButton(QString t_icon) {
	setIcon(resources::icon(t_icon));
	setObjectName("TitleButton");
}

ForgeTitleBar::ForgeTitleBar(QWidget* t_parent)
	: FWidget(t_parent)
{
	setDrag(true);
	setDragTarget(t_parent);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	layout->setSpacing(0);
	layout->setContentsMargins(5, 2, 5, 2);

	auto close = new ForgeTitleButton("close");

	(void)this->connect(close, &QPushButton::released,
		this, &ForgeTitleBar::closeControl);

	layout->addStretch(1);
	layout->addWidget(close);
	this->setLayout(layout);
	this->setMinimumWidth(100);
}

void ForgeTitleBar::closeControl() {
	auto p = (QDialog*)parent();
	if (p != nullptr)
		p->close();
}