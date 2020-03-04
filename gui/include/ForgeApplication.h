#pragma once

#include <algorithm>

#include <Qt3DExtras/QAbstractCameraController>
#include <QtWidgets/QApplication>
#include <Qt3DInput/QInputSettings>
#include <Qt3DRender/QFrameGraphNode>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QRenderAspect>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QLogicAspect>

#include "ForgeWindow.h"

typedef Qt3DExtras::QAbstractCameraController QtController;
typedef Qt3DInput::QInputSettings QtInputSettings;
typedef Qt3DRender::QFrameGraphNode QtFrameGraphNode;
typedef Qt3DRender::QRenderSettings QtRenderSettings;
typedef Qt3DCore::QAspectEngine QtAspectEngine;
typedef Qt3DRender::QRenderAspect QtRenderAspect;
typedef Qt3DInput::QInputAspect QtInputAspect;
typedef Qt3DLogic::QLogicAspect QtLogicAspect;
typedef Qt3DCore::QEntityPtr QtEntityPtr;



class ForgeController : public QtController {
private:
	inline float clampInputs(float input1, float input2) {
		float axisValue = input1 + input2;
		return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
	}

public:
	ForgeController() : QtController() {}

	void moveCamera(const QAbstractCameraController::InputState& state, float dt) {

		auto cam = camera();

		if (cam == nullptr)
			return;

		const QVector3D up(0.0f, 1.0f, 0.0f);

		if (state.rightMouseButtonActive) {
			// Orbit
			cam->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, up);
			cam->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
		}
	}
};

class ForgeApplication : public QApplication {
private:
	
	QDir rootPath;

	QDir resourcesPath;
	
	std::vector<ForgeWindow*> windows;

	QtInputSettings* inputSettings;

	QtFrameGraphNode* frameGraph;

	QtRenderSettings* renderSettings;

	QtAspectEngine* aspectEngine;

	QtRenderAspect* renderAspect;

	QtInputAspect* inputAspect;

	QtLogicAspect* logicAspect;

	QtEntityPtr rootEntity;

	ForgeController* controller;

public:

	ForgeApplication(int argc, char* argv[])
		: QApplication(argc, argv)
		, windows()
		, inputSettings(new QtInputSettings())
		, frameGraph(new QtFrameGraphNode())
		, renderSettings(new QtRenderSettings())
		, aspectEngine(new QtAspectEngine())
		, renderAspect(new QtRenderAspect())
		, inputAspect(new QtInputAspect())
		, logicAspect(new QtLogicAspect())
		, rootEntity(new QtEntity())
		, controller(new ForgeController())
	{
		rootPath = applicationDirPath();
		resourcesPath = QDir(rootPath.filePath("resources"));
		resources::initialize(resources());

		// initialize the default surface formate for all 
		// QWindow and QWindow derived components
		QSurfaceFormat format;
		format.setVersion(4, 3);
		format.setProfile(QSurfaceFormat::CoreProfile);
		format.setDepthBufferSize(24);
		format.setSamples(4);
		format.setStencilBufferSize(8);

		QSurfaceFormat::setDefaultFormat(format);

		// register aspects and set a base framegraph
		aspectEngine->registerAspect(renderAspect);
		aspectEngine->registerAspect(inputAspect);
		aspectEngine->registerAspect(logicAspect);

		renderSettings->setActiveFrameGraph(frameGraph);

		rootEntity->addComponent(renderSettings);
		rootEntity->addComponent(inputSettings);

		aspectEngine->setRootEntity(rootEntity);

		controller->setParent(rootEntity.data());
		controller->setLinearSpeed(50.0f);
		controller->setLookSpeed(100.0f);

		displayTest();
	}

	static ForgeApplication* instance() {
		return (ForgeApplication*)QApplication::instance();
	}

	QDir root() {
		return this->rootPath;
	}

	QDir resources() {
		return this->resourcesPath;
	}

	void show() {
		for (auto window : windows) {
			window->show();
		}
	}

	void addWindow(ForgeWindow* t_window) {
		t_window->setRenderSource(frameGraph);
		t_window->setRoot(rootEntity.data());
		(void)this->connect(t_window, &ForgeWindow::onFocus, 
							this, &ForgeApplication::onWindowFocus);

		(void)this->connect(t_window, &ForgeWindow::onClose, 
							this, &ForgeApplication::onWindowClose);

		windows.push_back(t_window);
		activeWindow(t_window);
	}

	void displayTest() {
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
		active->setParent(rootEntity.data());
	}

	void activeWindow(ForgeWindow* t_window) {
		if (t_window != nullptr) {
			controller->setCamera(t_window->getCamera());
			inputSettings->setEventSource(t_window);
		}
	}

	void onWindowFocus(ForgeWindow* t_window) {
		activeWindow(t_window);
	}

	void onWindowClose(ForgeWindow* t_window) {
		t_window->clearParent();
		std::remove_if(windows.begin(), windows.end(), 
			[t_window](auto w) {
				return t_window->isWindow(w);
			});
		if (windows.size() > 0) {
			activeWindow(windows.at(0));
		}
	}

};