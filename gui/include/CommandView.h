#pragma once

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

#include "FModel.h"
#include "FCrossSection.h"
#include "ForgeRenderer.h"

class TitleBar;

class TitleButton : public QPushButton {
public:
	TitleButton(QString t_icon);
};

class TitleBar : public QWidget {
private:

	void build();

public:
	TitleBar() {
		build();
	}

	void expandButtonPressed();

	void closeButtonPressed();
};

class CommandView : public QDockWidget {
	Q_OBJECT

private:


public:
	CommandView(QWidget* t_parent);

	void topLevelChanged(bool topLevel);

};

class CreateCommand : public CommandView {
private:

	QPushButton* button;

	FModel* active = nullptr;
	
	void track() {
		(void)this->connect(ForgeRenderer::instance(), &ForgeRenderer::mouseMove,
							this, &CreateCommand::onMouseEvent);

		(void)this->connect(ForgeRenderer::instance(), &ForgeRenderer::mouseRelease,
							this, &CreateCommand::onClickEvent);
	}

	void untrack() {
		(void)this->disconnect(ForgeRenderer::instance(), &ForgeRenderer::mouseMove,
							this, &CreateCommand::onMouseEvent);

		(void)this->disconnect(ForgeRenderer::instance(), &ForgeRenderer::mouseRelease,
							this, &CreateCommand::onClickEvent);
	}

	void onMouseEvent(QMouseEvent* e) {
		auto current = e->localPos();
		auto camera = ForgeRenderer::instance()->camera();
		auto screen = ForgeRenderer::instance()->getView()->rect();

		auto view = camera->viewMatrix();
		auto proj = camera->projectionMatrix();

		auto position = active->getTransform()->translation();
		position = position.project(view, proj, screen);

		position.setX(current.x());
		position.setY(screen.height() - current.y());

		position = position.unproject(view, proj, screen);
		active->getTransform()->setTranslation(position);
	}

	void onClickEvent(QMouseEvent* e) {
		active = nullptr;
		button->setEnabled(true);
		untrack();
	}

public:
	CreateCommand(QWidget* t_parent)
		: CommandView(t_parent)
		, active(nullptr)
	{
	
		auto layout = new QVBoxLayout();
		auto row    = new QHBoxLayout();

		auto name = new QLineEdit();
		name->setPlaceholderText("Item_Name");
		
		button = new QPushButton("Create");
		row->addStretch(1);
		row->addWidget(button);

		layout->addWidget(name);
		layout->addItem(row);

		(void)this->connect(button, &QPushButton::pressed,
							this, &CreateCommand::createStructure);

		layout->addStretch(1);
		this->widget()->setLayout(layout);
	}

	void createStructure() {
		FCrossSection crossSection({
			{-3.0f, 3.0f},
			{-3.0f, -3.0f},
			{-1.5f, -3.0f},
			{-1.5f, -1.5f},
			{1.5f, -1.5f},
			{1.5f, -3.0f},
			{3.0f, -3.0f},
			{3.0f, 3.0f},
			{1.5f, 3.0f},
			{1.5f, 1.5f},
			{-1.5f, 1.5f},
			{-1.5f, 3.0f}
		});

		active = new FModel(crossSection.toGeometry());
		ForgeRenderer::instance()->addModel(active);

		button->setEnabled(false);
		track();
	}

};