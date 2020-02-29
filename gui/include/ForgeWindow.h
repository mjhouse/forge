#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtCore/QDir>

#include "FCrossSection.h"
#include "MeshView.h"
#include "Config.h"

#include "ForgeMenu.h"
#include "ForgePlace.h"

class ForgeWindow: public QMainWindow {
private:

	MeshView view;

	Config config;

	FCrossSection* polygon;

	ForgeMenu*  mainMenu;
	ForgePlace* placeDialog;

public:
	ForgeWindow();
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
