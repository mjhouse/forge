#ifndef __FORGEMAINMENU_H__
#define __FORGEMAINMENU_H__

#include <QtWidgets/QMenuBar>

#include "ForgeControl.h"

enum class RootMenu {
	File,
	View,
	Settings
};

class ForgeMainMenu : public ForgeControl {
	Q_OBJECT

private:

	QMenu* m_fileMenu;		/*!< the "File" menu */

	QMenu* m_viewMenu;		/*!< the "View" menu */

	QMenu* m_settingsMenu;	/*!< the "Settings" menu */

	inline QMenu* bind(QMenuBar* t_menu, const char* t_name);

	inline QMenu* getMenu(RootMenu t_id);

public:
	ForgeMainMenu();

	void addLauncher(RootMenu t_root, const char* label, ForgeControl* t_control);

signals:
	void exitCommand(bool t_checked);
	
	void viewCommand(bool t_checked);
};

#endif // __FORGEMAINMENU_H__