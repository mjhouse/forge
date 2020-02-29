#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtCore/QDir>

#include "FCrossSection.h"
#include "MeshView.h"
#include "Config.h"

class ForgeWindow: public QMainWindow {
private:
	QDir resources;

	MeshView view;

	Config config;

	FCrossSection* polygon;

	FModel* model;

public:
	ForgeWindow( QDir t_resources );
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
