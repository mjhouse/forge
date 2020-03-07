#include "ForgeMainMenu.h"

inline QMenu* ForgeMainMenu::bind(QMenuBar* t_menu, const char* t_name) {
	auto menu = new QMenu(tr(t_name), this);
	t_menu->addMenu(menu);
	return menu;
}

inline void ForgeMainMenu::bind(QMenu* t_menu, const char* t_name, void(ForgeMainMenu::*t_callback)(bool)) {
	(void)this->connect(t_menu->addAction(tr(t_name)), &QAction::triggered,
						this, t_callback);
}

ForgeMainMenu::ForgeMainMenu() {
	this->hasTitle(false);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	// File Menu
	auto f = bind(menu, "File");
	bind(f, "Exit", &ForgeMainMenu::exitCommand);

	// View Menu
	auto v = bind(menu, "View");
	bind(v, "3D Window", &ForgeMainMenu::viewCommand);
	bind(v, "Move", &ForgeMainMenu::moveCommand);
	bind(v, "Create", &ForgeMainMenu::createCommand);
	
	// Settings Menu
	auto s = bind(menu, "Settings");
	bind(s, "Options", &ForgeMainMenu::optionsCommand);

	layout->addWidget(menu);
	layout->addStretch(1);

	widget->setDrag(true);
	widget->setDragTarget(this);
	widget->setLayout(layout);

	this->setHandle(widget);
	this->setCentralWidget(widget);
	this->setObjectName("MainMenu");
}