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

#define WHITE 0xffffff
#define BLACK 0x000000
#define GRAY  0x212121

ForgeWindow::ForgeWindow( QDir t_resources ) 
	: resources(t_resources)
	, view(GRAY)
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

	// TEST TEST TEST

	// MATERIAL	
	//auto material = new Qt3DExtras::QGoochMaterial();
	//material->setCool(0x002fff);
	//material->setWarm(0xff0000);
	//material->setDiffuse(WHITE);
	//material->setAlpha(0.01);
	//material->setBeta(0.25);
	//material->setShininess(0.1);
	
	auto material = new FDefaultMaterial(resources);

	
	// SETUP ENTITY
	auto entity = view.rootEntity();
	polygon = new FCrossSection(entity, material,{
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

	// create the floating main menu
	auto menu = new ForgeMenu(this);

	(void)this->connect(menu, &ForgeMenu::onOpenFile,
						this, &ForgeWindow::openFile);

	(void)this->connect(menu, &ForgeMenu::onExitForge,
						this, &ForgeWindow::exitForge);

	(void)this->connect(menu, &ForgeMenu::onOpenConfig,
						this, &ForgeWindow::openConfig);

	(void)this->connect(menu, &ForgeMenu::onTestEvent,
						this, &ForgeWindow::testEvent);

	// setting dock options = 0 will remove dockarea animations,
	// which stutter because of the 3d view
	this->setDockOptions(0);
	this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, menu);

	// wrapped 3d view is the main, and only widget
    this->setCentralWidget(main);
}

void ForgeWindow::openFile(QString path) {
	//auto material = new QPhongMaterial(view.rootEntity());
	//material->setDiffuse(QColor(QRgb(0x665423)));
	//material->setAmbient(QColor(QRgb(0xffffff)));
	//material->setSpecular(QColor(QRgb(0xff0000)));

	//auto entity = new QEntity(view.rootEntity());
	//auto mesh = new QMesh(view.rootEntity());

	//Qt3DCore::QTransform* transform = new Qt3DCore::QTransform;
	//transform->setTranslation(QVector3D(0,0,0));

	//entity->addComponent(mesh);
	//entity->addComponent(material);
	//entity->addComponent(transform);

	// mesh->setSource(QUrl::fromLocalFile("C:\\Work\\experimental\\Forge\\resources\\test\\projection_model.obj"));
}

void ForgeWindow::exitForge() {
	QApplication::quit();
}

void ForgeWindow::openConfig() {
	config.exec();
}

void ForgeWindow::testEvent() {
	polygon->thicken();
}
