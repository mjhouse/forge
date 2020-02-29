#pragma once

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

#include "FModel.h"

class TitleBar : public QWidget {
private:
public:
	TitleBar() {
		auto layout  = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
		auto pop_btn = new QPushButton();
		auto cls_btn = new QPushButton();

		pop_btn->setIcon(resources::icon("pop"));
		pop_btn->setObjectName("TitleButton");

		cls_btn->setIcon(resources::icon("close"));
		cls_btn->setObjectName("TitleButton");

		layout->addStretch(1);
		layout->addWidget(pop_btn);
		layout->addWidget(cls_btn);

		this->setLayout(layout);
	}
};

class ForgePlace : public QDockWidget {
	Q_OBJECT

private:

	FModel* model;

public:
	ForgePlace(QWidget* t_parent)
		: QDockWidget(t_parent)
		, model(nullptr)
	{
		this->setTitleBarWidget(new TitleBar());
		this->setWidget(new QWidget());

		this->setObjectName("Control");
	}

};