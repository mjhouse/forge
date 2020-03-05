#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>
#include <QtGui/QMouseEvent>

#include "Resources.h"
#include "FWidget.h"

class ForgeTitleButton : public QPushButton {
public:
	ForgeTitleButton(QString t_icon);
};

class ForgeTitleBar : public FWidget {
private:

public:
	ForgeTitleBar(QWidget* t_parent);

	void closeControl();

};