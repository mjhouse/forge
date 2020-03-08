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

#include "IdentifierList.h"
#include "ForgeWindow.h"
#include "ForgeControl.h"
#include "FModel.h"

typedef Qt3DExtras::QOrbitCameraController QtController;
typedef Qt3DInput::QInputSettings QtInputSettings;
typedef Qt3DRender::QFrameGraphNode QtFrameGraphNode;
typedef Qt3DRender::QRenderSettings QtRenderSettings;
typedef Qt3DCore::QAspectEngine QtAspectEngine;
typedef Qt3DRender::QRenderAspect QtRenderAspect;
typedef Qt3DInput::QInputAspect QtInputAspect;
typedef Qt3DLogic::QLogicAspect QtLogicAspect;
typedef Qt3DCore::QEntityPtr QtEntityPtr;

using namespace components;

class ForgeApplication : public QApplication {
private:
	
	QDir rootPath;

	QDir resourcesPath;

	IdentifierList<ForgeWindow> container;

	IdentifierList<ForgeControl> m_controls;

	QtInputSettings* inputSettings;

	QtFrameGraphNode* frameGraph;

	QtRenderSettings* renderSettings;

	QtAspectEngine aspectEngine;

	QtRenderAspect* renderAspect;

	QtInputAspect* inputAspect;

	QtLogicAspect* logicAspect;

	QtEntityPtr rootEntity;

	QtController* controller;

	FModel* m_selected;

	void setActive(ForgeWindow* t_window);

	void onWindowClose(ForgeWindow* t_window);

	void initialize();

public:

	ForgeApplication(int argc, char* argv[]);

	~ForgeApplication(){}

	static ForgeApplication* instance();
	

	QDir root();

	QDir resources();
	
	ForgeWindow* newWindow();

	ForgeWindow* findWindow(QPoint t_point);

	FModel* getSelected();

	void setSelected(FModel* t_model);

	void render(FModel* t_model);
	
	void onExit(bool t_checked);

	void onView(bool t_checked);

	void onLaunch(int t_id);
};