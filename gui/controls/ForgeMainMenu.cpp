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
	this->setPersistent(true);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	// File Menu
	m_fileMenu = bind(menu, "File");
	bind(m_fileMenu, "Exit", &ForgeMainMenu::exitCommand);

	// View Menu
	m_viewMenu = bind(menu, "View");
	bind(m_viewMenu, "3D View", &ForgeMainMenu::viewCommand);
	
	// Settings Menu
	m_settingsMenu = bind(menu, "Settings");

	layout->addWidget(menu);
	layout->addStretch(1);

	widget->setDrag(true);
	widget->setDragTarget(this);
	widget->setLayout(layout);

	this->setHandle(widget);
	this->setCentralWidget(widget);
	this->setObjectName("MainMenu");
}

void ForgeMainMenu::addLauncher(RootMenu t_root, const char* label, ForgeControl* t_control) {
	auto menu = getMenu(t_root);
	(void)this->connect(menu->addAction(tr(label)), &QAction::triggered,
		[t_control](bool c) {
			t_control->show();
	});
}