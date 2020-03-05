#pragma once

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QStyle>

#include "FModel.h"
#include "FCrossSection.h"
#include "ForgeRenderer.h"

enum class ShortcutKey {
	EscapeKey,
	EnterKey
};

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

class Command : public QDockWidget {
private:

	static Command* command;

	std::vector<QShortcut*> shortcuts;

	void clearActive();

	void setActive(Command* t_command);
	
	void focusInEvent(QFocusEvent* e) override;
	
	void closeEvent(QCloseEvent* e) override;

	void visibilityEvent(bool t_visible);

	void unlisten();

	void listen();

	void onDockChanged(bool t_floating);

public:
	Command(QWidget* t_parent);

	virtual void onActivated();

	virtual void onDeactivated();

	virtual void onMove(QMouseEvent* e);

	virtual void onClick(QMouseEvent* e);

	virtual void onShortcut(ShortcutKey key);

};