#pragma once

#include <QtWidgets/QDialog>

#include "ForgeTitleBar.h"
#include "ForgeWindow.h"

#include "HasIdentifier.h"

using namespace components;

class ForgeControl : public QDialog, public HasIdentifier {
private:

	ForgeWindow* m_parent;

	ForgeTitleBar* m_title;

	QWidget* m_body;

	FWidget* m_handle;

	void findParent(QPoint t_point);

	void moveEvent(QMoveEvent* t_event) override;

public:

	ForgeControl();

	void hasTitle(bool t_title);

	void setCentralWidget(QWidget* t_widget);

	void setHandle(FWidget* t_handle);

	bool isControl(ForgeControl* t_control);

	void stateChanged(Qt::ApplicationState state);

};