#pragma once

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

	QMenu* m_fileMenu;

	QMenu* m_viewMenu;

	QMenu* m_settingsMenu;


	inline QMenu* bind(QMenuBar* t_menu, const char* t_name);

	inline void bind(QMenu* t_menu, const char* t_name, void(ForgeMainMenu::*callback)(bool));

	inline QMenu* getMenu(RootMenu t_id) {
		switch (t_id) {
			case RootMenu::File: return m_fileMenu;
			case RootMenu::View: return m_viewMenu;
			case RootMenu::Settings: return m_settingsMenu;
			default: return nullptr;
		}
	}

public:
	ForgeMainMenu();

	void addLauncher(RootMenu t_root, const char* label, ForgeControl* t_control);


signals:
	void exitCommand(bool t_checked);
	void viewCommand(bool t_checked);
	void launchCommand(int t_id);
};