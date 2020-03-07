#include "ForgeTransformMenu.h"

inline QMenu* ForgeTransformMenu::bind(QMenuBar* t_menu, const char* t_name) {
	auto menu = new QMenu(tr(t_name), this);
	t_menu->addMenu(menu);
	return menu;
}

inline void ForgeTransformMenu::bind(QMenu* t_menu, const char* t_name, void(ForgeTransformMenu::*t_callback)(bool)) {
	(void)this->connect(t_menu->addAction(tr(t_name)), &QAction::triggered,
						this, t_callback);
}

ForgeTransformMenu::ForgeTransformMenu() {
	//this->hasTitle(false);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	// File Menu
	auto f = bind(menu, "File");
	bind(f, "Exit", &ForgeMainMenu::exitCommand);

	// View Menu
	auto v = bind(menu, "View");
	bind(v, "3D Window", &ForgeMainMenu::viewCommand);
	bind(v, "Member Placement", &ForgeMainMenu::placeCommand);
	
	// Settings Menu
	auto s = bind(menu, "Settings");
	bind(s, "Options", &ForgeMainMenu::optionsCommand);

	layout->addWidget(menu);
	layout->addStretch(1);

	//widget->setDrag(true);
	//widget->setDragTarget(this);
	widget->setLayout(layout);

	//this->setHandle(widget);
	this->setCentralWidget(widget);
	this->setObjectName("TransformMenu");
}