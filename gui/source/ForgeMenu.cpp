#include "ForgeMenu.h"
#include "ForgeWindow.h"

#include <QtWidgets/QLayout>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtGui/QMouseEvent>

#include <iostream>

ForgeMenu::ForgeMenu( QWidget* parent ) {
	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

	auto widget = new QWidget();
	auto menu = new QMenuBar();

	auto f_menu = new QMenu(tr("File"), this);
	auto v_menu = new QMenu(tr("View"), this);
	auto s_menu = new QMenu(tr("Settings"), this);

	// submenu/items for file menu
	auto exit_action = f_menu->addAction(tr("Exit"));

	// submenu/items for view menu
	auto create_action = v_menu->addAction(tr("Create"));
	create_action->setCheckable(true);

	// submenu/items for settings menu
	auto test_action = s_menu->addAction(tr("Test"));
	auto options_action = s_menu->addAction(tr("Options"));

	menu->addMenu(f_menu);
	menu->addMenu(v_menu);
	menu->addMenu(s_menu);

	layout->addWidget(menu);
	layout->addStretch(1);

	widget->setLayout(layout);
	this->setTitleBarWidget(widget);

	this->setWidget(new QWidget());
	this->widget()->setMaximumHeight(0);

	this->setAllowedAreas(Qt::DockWidgetArea::TopDockWidgetArea | Qt::DockWidgetArea::BottomDockWidgetArea);
	   
	(void)this->connect(this, &QDockWidget::topLevelChanged, 
						this, &ForgeMenu::onOwnerChanged);

	(void)this->connect(this, &QDockWidget::dockLocationChanged,
						this, &ForgeMenu::onDockChanged);

	(void)this->connect(exit_action, &QAction::triggered,
						this, &ForgeMenu::exitButton);

	(void)this->connect(create_action, &QAction::triggered,
						this, &ForgeMenu::createButton);

	(void)this->connect(test_action, &QAction::triggered,
						this, &ForgeMenu::testButton);

	(void)this->connect(options_action, &QAction::triggered,
						this, &ForgeMenu::optionButton);

	this->setObjectName("MainControl");
}

void ForgeMenu::onOwnerChanged(bool topLevel) {
	if (topLevel) {
		this->widget()->setMaximumWidth(300);
	}
	else {
		this->widget()->setMaximumWidth(QWIDGETSIZE_MAX);
	}
}

void ForgeMenu::onDockChanged(Qt::DockWidgetArea area) {

}

void ForgeMenu::exitButton(bool checked) {
	emit onExitForge();
}

void ForgeMenu::createButton(bool checked) {
	emit onCreateCommand(checked);
}

void ForgeMenu::testButton(bool checked) {
	emit onTestEvent();
}

void ForgeMenu::optionButton(bool checked) {
	emit onOpenConfig();
}