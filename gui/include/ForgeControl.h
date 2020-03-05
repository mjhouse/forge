#pragma once

#include <QtWidgets/QDialog>

#include "ForgeTitleBar.h"

class ForgeControl : public QDialog {
private:

	ForgeTitleBar* m_title;

	QWidget* m_body;
	
public:
	ForgeControl();

	void hasTitle(bool t_title);

	void setCentralWidget(QWidget* t_widget);

	void stateChanged(Qt::ApplicationState state);
};