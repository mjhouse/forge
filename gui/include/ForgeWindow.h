#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtCore/QDir>

#include "MeshView.h"
#include "Config.h"
#include "FCrossSection.h"

class ForgeWindow: public QMainWindow {
private:
	QDir resources;

	MeshView view;

	Config config;

	FCrossSection* polygon;

public:
	ForgeWindow( QDir t_resources );
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
