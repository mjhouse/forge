#pragma once

#include "CommandBase.h"

class CreateCommand : public Command {
private:

	QPushButton* button;

	FModel* active = nullptr;

	float length = 0.5;

public:
	CreateCommand(QWidget* t_parent)
		: Command(t_parent)
		, active(nullptr)
	{

		auto layout = new QVBoxLayout();
		auto row = new QHBoxLayout();

		auto name = new QLineEdit();
		name->setPlaceholderText("Length");

		button = new QPushButton("Create");
		row->addStretch(1);
		row->addWidget(button);

		layout->addWidget(name);
		layout->addItem(row);

		(void)this->connect(button, &QPushButton::pressed,
			this, &CreateCommand::startCreate);

		(void)this->connect(name, &QLineEdit::textChanged,
							this, &CreateCommand::lengthChanged);

		layout->addStretch(1);
		this->widget()->setLayout(layout);
	}

	void onMove(QMouseEvent* e) override {
		if (active) {
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
	}

	void cancelCreate() {
		if (active != nullptr) {
			active->setParent((QtEntity*)nullptr);
			delete active;
			active = nullptr;
		}
		button->setEnabled(true);
	}

	void finishCreate() {
		active = nullptr;
		button->setEnabled(true);
	}

	void startCreate() {
		cancelCreate();
		FCrossSection* cs = new FCrossSection({
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

		cs->setLength(length);
		active = new FModel(cs);
		ForgeRenderer::instance()->addModel(active);

		button->setEnabled(false);
	}

	void onClick(QMouseEvent* e) override {
		finishCreate();
	}

	void onShortcut(ShortcutKey t_key) override {
		switch (t_key) {
			case ShortcutKey::EscapeKey:
				cancelCreate();
				break;
			case ShortcutKey::EnterKey:
				finishCreate();
				break;
			default: 
				break;
		}
	}

	void lengthChanged(QString t_input) {
		bool ok = false;
		auto l = t_input.toFloat(&ok);
		if (ok) {
			length = l;
			if(active) 
				active->setLength(length);
		}
	}

};