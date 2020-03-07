#pragma once

#include <QtWidgets/QMenuBar>

#include "ForgeControl.h"

class ForgeTransformMenu : public ForgeControl {
	Q_OBJECT

private:

	inline QMenu* bind(QMenuBar* t_menu, const char* t_name);

	inline void bind(QMenu* t_menu, const char* t_name, void(ForgeTransformMenu::*callback)(bool));

public:
	ForgeTransformMenu();

signals:
	void exitCommand(bool t_checked);
	void viewCommand(bool t_checked);
	void placeCommand(bool t_checked);
	void optionsCommand(bool t_checked);
};