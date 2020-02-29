#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QDockWidget>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QLineWidth>

#include "ForgeWindow.h"
#include "ForgeMenu.h"
#include "MeshView.h"
#include "Config.h"
#include "FCrossSection.h"
#include "FDefaultMaterial.h"
#include "ForgePlace.h"

#define WHITE 0xffffff
#define BLACK 0x000000
#define GRAY  0x212121

ForgeWindow::ForgeWindow() 
	: view(GRAY)
	, config()
	, polygon(nullptr) {

	QRect screenSize = QDesktopWidget().availableGeometry(this);
	resize(screenSize.size() * 0.8);
	setWindowTitle("Forge - Construction");
}

ForgeWindow::~ForgeWindow() {

}

void ForgeWindow::build() {
	// wrap the 3d view in a QWidget container
	auto main = QWidget::createWindowContainer(&view);

	// SETUP ENTITY
	auto entity = view.rootEntity();
	
	polygon = new FCrossSection({
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

	new FModel(entity,polygon->toGeometry());

	mainMenu = new ForgeMenu(this);
	placeDialog = new ForgePlace(this);

	(void)this->connect(mainMenu, &ForgeMenu::onOpenFile,
						this, &ForgeWindow::openFile);

	(void)this->connect(mainMenu, &ForgeMenu::onExitForge,
						this, &ForgeWindow::exitForge);

	(void)this->connect(mainMenu, &ForgeMenu::onOpenConfig,
						this, &ForgeWindow::openConfig);

	(void)this->connect(mainMenu, &ForgeMenu::onTestEvent,
						this, &ForgeWindow::testEvent);

	// setting dock options = 0 will remove dockarea animations,
	// which stutter because of the 3d view
	this->setDockOptions(0);
	
	this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, mainMenu);
	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, placeDialog);

	placeDialog->hide();

	// wrapped 3d view is the main and only widget
    this->setCentralWidget(main);
}

void ForgeWindow::openFile(QString path) {

}

void ForgeWindow::exitForge() {
	QApplication::quit();
}

void ForgeWindow::openConfig() {
	config.exec();
}

void ForgeWindow::testEvent() {
	placeDialog->show();
}
