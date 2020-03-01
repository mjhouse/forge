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
#include "Config.h"
#include "FCrossSection.h"
#include "FDefaultMaterial.h"
#include "CommandView.h"
#include "ForgeRenderer.h"

#define WHITE 0xffffff
#define BLACK 0x000000
#define GRAY  0x212121

ForgeWindow::ForgeWindow() 
	: config()
	, mainMenu(new ForgeMenu(this))
	, placeDialog(new CreateCommand(this))
	{

	QRect screenSize = QDesktopWidget().availableGeometry(this);
	resize(screenSize.size() * 0.8);
	setWindowTitle("Forge - Construction");
	ForgeRenderer::instance()->setBackground(GRAY);
}

ForgeWindow::~ForgeWindow() {

}

void ForgeWindow::build() {

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
    this->setCentralWidget(ForgeRenderer::instance()->getView());
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
