#pragma once

#include <QtWidgets/QDockWidget>

class ForgeMenu : public QDockWidget {
	Q_OBJECT
private:

public:
	ForgeMenu( QWidget* parent );

	void onOwnerChanged(bool topLevel);
	void onDockChanged(Qt::DockWidgetArea area);

	void openButton(bool checked);
	void exitButton(bool checked);
	void testButton(bool checked);
	void optionButton(bool checked);

signals:
	void onOpenFile(QString path);
	void onExitForge();
	void onTestEvent();
	void onOpenConfig();
};