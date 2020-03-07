#pragma once

#include <QtWidgets/QMenuBar>

#include "ForgeControl.h"

class ForgeMainMenu : public ForgeControl {
	Q_OBJECT

private:

	inline QMenu* bind(QMenuBar* t_menu, const char* t_name);

	inline void bind(QMenu* t_menu, const char* t_name, void(ForgeMainMenu::*callback)(bool));

public:
	ForgeMainMenu();

signals:
	void exitCommand(bool t_checked);
	void viewCommand(bool t_checked);
	void moveCommand(bool t_checked);
	void createCommand(bool t_checked);
	void optionsCommand(bool t_checked);
};