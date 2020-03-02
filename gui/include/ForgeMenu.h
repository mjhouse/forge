#pragma once

#include <QtWidgets/QDockWidget>

class ForgeMenu : public QDockWidget {
	Q_OBJECT
private:

public:
	ForgeMenu( QWidget* parent );

	void onOwnerChanged(bool topLevel);
	void onDockChanged(Qt::DockWidgetArea area);

	void exitButton(bool checked);
	void createButton(bool checked);
	void testButton(bool checked);
	void optionButton(bool checked);

signals:
	void onExitForge();
	void onCreateCommand(bool open);
	void onTestEvent();
	void onOpenConfig();
};