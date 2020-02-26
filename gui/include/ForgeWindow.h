#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>

#include "MeshView.h"
#include "Config.h"
#include "Geometry.h"

class ForgeWindow: public QMainWindow {
private:
	MeshView view;
	Config config;

<<<<<<< HEAD
	FCrossSection* polygon;
=======
	// TEST TEST
	FCube* cube;
	FPolygon* polygon;
	FLine* line;
>>>>>>> parent of c042836... Adds thickening algo to FPolygon, some refactors

public:
	ForgeWindow();
	~ForgeWindow();

	void build();

	void openFile(QString path);
	void exitForge();
	void openConfig();
	void testEvent();
};
