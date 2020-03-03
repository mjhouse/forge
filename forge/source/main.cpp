#include <iostream>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QAbstractCameraController>

#include <Qt3DRender/QViewport>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QRenderAspect>
#include <QtGui/QWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DInput/QInputSettings>
#include <Qt3DLogic/QLogicAspect>

#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeApplication.h"
#include "ForgeWindow.h"
#include "Resources.h"
#include "Defines.h"

#define WHITE  QColor(QRgb(0xffffff))
#define BLACK  QColor(QRgb(0x000000))
#define GRAY   QColor(QRgb(0x212121))

class FCameraController : public Qt3DExtras::QAbstractCameraController {

	bool enable;

public:
	FCameraController(bool e, QtEntity* t_parent) 
		: Qt3DExtras::QAbstractCameraController(t_parent)
		, enable(e) 
	{

	}

	inline float clampInputs(float input1, float input2)
	{
		float axisValue = input1 + input2;
		return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
	}

	void moveCamera(const QAbstractCameraController::InputState& state, float dt) override {
		Qt3DRender::QCamera* theCamera = camera();

		if (theCamera == nullptr || !enable)
			return;

		const QVector3D upVector(0.0f, 1.0f, 0.0f);

		// Mouse input
		if (state.leftMouseButtonActive) {
			theCamera->translate(QVector3D(clampInputs(state.rxAxisValue, state.txAxisValue) * linearSpeed(),
				clampInputs(state.ryAxisValue, state.tyAxisValue) * linearSpeed(),
				0) * dt);
			return;
		}
		else if (state.rightMouseButtonActive) {
			// Orbit
			theCamera->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, upVector);
			theCamera->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
		}
	}

};

void test() {

	QSurfaceFormat format;
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setDepthBufferSize(24);
	format.setSamples(4);
	format.setStencilBufferSize(8);

	QSurfaceFormat::setDefaultFormat(format);

	auto window1 = new QWindow();
	auto window2 = new QWindow();
	
	window1->setSurfaceType(QWindow::OpenGLSurface);
	window2->setSurfaceType(QWindow::OpenGLSurface);

	window1->resize(640, 480);
	window2->resize(640, 480);

	auto inset = new Qt3DInput::QInputSettings();
	
	auto framegraph = new Qt3DRender::QFrameGraphNode();
	auto settings = new Qt3DRender::QRenderSettings();

	auto engine = new Qt3DCore::QAspectEngine();
	auto render = new Qt3DRender::QRenderAspect();
	auto input = new Qt3DInput::QInputAspect();
	auto logic = new Qt3DLogic::QLogicAspect();
	
	Qt3DCore::QEntityPtr entity(new QtEntity());

	engine->registerAspect(render);
	engine->registerAspect(input);
	engine->registerAspect(logic);

	settings->setActiveFrameGraph(framegraph);

	inset->setEventSource(window1);
	
	entity->addComponent(settings);
	entity->addComponent(inset);

	engine->setRootEntity(entity);
	
	FCrossSection* cs = new FCrossSection({
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

	cs->setLength(0.25);
	auto active = new FModel(cs);
	active->setParent(entity.data());


	// CAMERAS
	auto camera1 = new Qt3DRender::QCamera();
	camera1->lens()->setPerspectiveProjection(45.0, 1, 0.1f, 1000.0);
	camera1->setPosition(QVector3D(0, 0, 10));
	camera1->setUpVector(QVector3D(0, 0, 1));
	camera1->setViewCenter(QVector3D(0, 0, 0));

	auto camera2 = new Qt3DRender::QCamera();
	camera2->lens()->setPerspectiveProjection(45.0, 1, 0.1f, 1000.0);
	camera2->setPosition(QVector3D(0, 10, 0));
	camera2->setUpVector(QVector3D(0, 0, 1));
	camera2->setViewCenter(QVector3D(0, 0, 0));

	// WINDOW #1
	auto renderer1 = new Qt3DExtras::QForwardRenderer();
	renderer1->setCamera(camera1);
	renderer1->setSurface(window1);
	renderer1->setClearColor(GRAY);

	// WINDOW #2
	auto renderer2 = new Qt3DExtras::QForwardRenderer();
	renderer2->setCamera(camera2);
	renderer2->setSurface(window2);
	renderer2->setClearColor(GRAY);

	// ADD WINDOWS TO SCENE
	renderer1->setParent(framegraph);
	renderer2->setParent(framegraph);

	auto controller1 = new FCameraController(true, entity.data());
	controller1->setLinearSpeed(50.0f);
	controller1->setLookSpeed(100.0f);

	controller1->setCamera(camera1);
	inset->setEventSource(window1);

	//auto controller2 = new FCameraController(true, entity.data());
	//controller2->setLinearSpeed(50.0f);
	//controller2->setLookSpeed(100.0f);
	//controller2->setCamera(camera2);
	
	window1->show();
	window2->show();
}

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);

	resources::initialize(app.resources());
	app.setStyleSheet(resources::theme("stylesheet"));

	test();

	//ForgeWindow window;
	//window.build();
	//window.show();
	
	return app.exec();
}