#include "ForgeMainMenu.h"

/*! \brief Inline helper function to create a new root menu.
 */
inline QMenu* ForgeMainMenu::bind(QMenuBar* t_menu, const char* t_name) {
	auto menu = new QMenu(tr(t_name), this);
	t_menu->addMenu(menu);
	return menu;
}

/*! \brief Map a RootMenu enum to a QMenu object.
 */
inline QMenu* ForgeMainMenu::getMenu(RootMenu t_id) {
	switch (t_id) {
		case RootMenu::File: return m_fileMenu;
		case RootMenu::View: return m_viewMenu;
		case RootMenu::Settings: return m_settingsMenu;
		default: return nullptr;
	}
}

/*! \brief The constructor for the main menu widget.
 */
ForgeMainMenu::ForgeMainMenu(ForgeWindow* t_parent) 
	: ForgeControl(t_parent,0.02,0.02) 
{

	this->hasTitle(false);
	this->setPersistent(true);

	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	// File Menu
	m_fileMenu = bind(menu, "File");
	(void)this->connect(m_fileMenu->addAction(tr("Exit")), &QAction::triggered,
						this, &ForgeMainMenu::exitCommand);

	// View Menu
	m_viewMenu = bind(menu, "View");
	(void)this->connect(m_viewMenu->addAction(tr("3D View")), &QAction::triggered,
						this, &ForgeMainMenu::viewCommand);
	
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

/*! \brief This binds an existing widget to a menu option,
 *		   so that clicking the menu displays the widget.
 */
void ForgeMainMenu::addLauncher(RootMenu t_root, const char* label, ForgeControl* t_control) {
	auto menu = getMenu(t_root);
	(void)this->connect(menu->addAction(tr(label)), &QAction::triggered,
		[t_control](bool c) {
			t_control->show();
	});
}