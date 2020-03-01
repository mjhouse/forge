#include "CommandView.h"

TitleButton::TitleButton(QString t_icon) {
	this->setIcon(resources::icon(t_icon));
	this->setObjectName("TitleButton");
};

void TitleBar::build() {
	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto expand_btn = new TitleButton("expand");
	auto close_btn = new TitleButton("close");

	layout->addStretch(1);
	layout->addWidget(expand_btn);
	layout->addWidget(close_btn);

	(void)this->connect(expand_btn, &QPushButton::pressed,
		this, &TitleBar::expandButtonPressed);
	(void)this->connect(close_btn, &QPushButton::pressed,
		this, &TitleBar::closeButtonPressed);

	this->setLayout(layout);
	this->setObjectName("TitleBar");
}

void TitleBar::expandButtonPressed() {
	auto parent = (QDockWidget*)this->parent();
	if (!parent->isFloating())
		parent->setFloating(true);
}

void TitleBar::closeButtonPressed() {
	((QDockWidget*)this->parent())->close();
}

CommandView::CommandView(QWidget* t_parent)
	: QDockWidget(t_parent)
{
	this->setTitleBarWidget(new TitleBar());
	this->setWidget(new QWidget());

	this->setAllowedAreas(
		Qt::DockWidgetArea::LeftDockWidgetArea |
		Qt::DockWidgetArea::RightDockWidgetArea);

	(void)this->connect(this, &QDockWidget::topLevelChanged,
						this, &CommandView::topLevelChanged);

	this->setMinimumWidth(100);
	this->setObjectName("Control");
}

void CommandView::topLevelChanged(bool topLevel) {
	if (topLevel) {
		auto size = this->sizeHint();
		this->resize(size);
	}
}