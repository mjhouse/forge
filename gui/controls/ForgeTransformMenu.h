#pragma once

#include <QtWidgets/QMenuBar>

#include "ForgeControl.h"

class ForgeTransformMenu : public ForgeControl {
	Q_OBJECT

private:

	QLineEdit* px;

	QLineEdit* py;

	QLineEdit* pz;

	QLineEdit* rx;

	QLineEdit* ry;

	QLineEdit* rz;

	QPushButton *m_button;

	inline QMenu* bind(QMenuBar* t_menu, const char* t_name);

	inline void bind(QMenu* t_menu, const char* t_name, void(ForgeTransformMenu::*callback)(bool));

public:
	ForgeTransformMenu();
	void onChange(bool checked);
	void onSet(bool checked);

	void showAt(int ax, int ay)
	{
		this->show();
		this->move(ax, ay);
	}

signals:
	void exitCommand(bool t_checked);
	void optionsCommand(bool t_checked);
};