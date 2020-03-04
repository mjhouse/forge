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
#include "ForgeRenderer.h"

#define WHITE 0xffffff
#define BLACK 0x000000
#define GRAY  0x212121

int ForgeWindow::count = 0;

bool CloseEventFilter::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::Close) {
		auto window = (ForgeWindow*)obj;
		emit window->onClose(window);
	}

	return QObject::eventFilter(obj, event);
}

ForgeWindow::ForgeWindow()
	: id(count++)
	, camera(new QtCamera())
	, renderer(new QtForwardRenderer())
{

	this->setSurfaceType(QWindow::OpenGLSurface);
	this->resize(1024, 768);

	camera->lens()->setPerspectiveProjection(45.0, (float)1024/768, 0.1f, 1000.0);
	camera->setPosition(QVector3D(0, 10, 0));
	camera->setUpVector(QVector3D(0, 0, 1));
	camera->setViewCenter(QVector3D(0, 0, 0));

	renderer->setCamera(camera);
	renderer->setSurface(this);
	renderer->setClearColor(GRAY);

	this->installEventFilter(new CloseEventFilter(this));

	//// setting dock options = 0 will remove dockarea animations,
	//// which stutter because of the 3d view
	//this->setDockOptions(0);
	//this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, EXAMPLE);

}

ForgeWindow::~ForgeWindow() {
	//delete camera;
	//delete renderer;
}

void ForgeWindow::setRenderSource(QtFrameGraphNode* t_framegraph) {
	renderer->setParent(t_framegraph);
}

void ForgeWindow::setRoot(QtEntity* t_root) {
	camera->setParent(t_root);
}

void ForgeWindow::focusInEvent(QFocusEvent* ev) {
	emit onFocus(this);
}

bool ForgeWindow::isWindow(ForgeWindow* t_window) {
	return t_window->id == this->id;
}
void ForgeWindow::clearParent() {
	renderer->setParent((QtFrameGraphNode*)nullptr);
	camera->setParent((QtEntity*)nullptr);
}


