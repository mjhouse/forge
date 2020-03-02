#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtCore/QDir>

#include "FCrossSection.h"
#include "Config.h"

#include "ForgeMenu.h"
#include "CommandCreate.h"

class ForgeWindow: public QMainWindow {
private:
	
	Config config;
	
	ForgeMenu*  mainMenu;

	// commands
	CreateCommand* placeDialog;

public:
	ForgeWindow();
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
