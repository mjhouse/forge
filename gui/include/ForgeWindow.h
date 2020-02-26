#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>

#include "MeshView.h"
#include "Config.h"
#include "FCrossSection.h"

class ForgeWindow: public QMainWindow {
private:
	MeshView view;
	Config config;

	FCrossSection* polygon;

public:
	ForgeWindow();
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
