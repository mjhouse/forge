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
#include <QPickingSettings>
#include <Qt3DRender/QRenderStateSet>
#include <Qt3DRender/QLineWidth>

#include "IdentifierList.h"
#include "ForgeWindow.h"
#include "ForgeControl.h"
#include "FCameraController.h"
#include "FModel.h"
#include "Defines.h"

class FCameraController;

using namespace components;

class ForgeApplication : public QApplication {

	Q_OBJECT

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

	FCameraController* controller;

	QtObjectPicker* m_picker;
	
	FModel* m_selected;
	
	void setActive(ForgeWindow* t_window);

	void onWindowClose(ForgeWindow* t_window);

	void onClick(Qt3DRender::QPickEvent* t_event);

	void initialize();

public:

	ForgeApplication(int argc, char* argv[]);

	~ForgeApplication(){}

	static ForgeApplication* instance();

	QDir root();

	QDir resources();
	
	ForgeWindow* newWindow();

	void onShownWindow(ForgeWindow* t_window);

	ForgeWindow* findWindow(QPoint t_point);

	FModel* getSelected();

	void setSelected(FModel* t_model);

	void render(FModel* t_model);
	
	void onExit(bool t_checked);

	void onView(bool t_checked);

	void onLaunch(int t_id);

	void reassign(ForgeWindow* t_parent, ForgeControl* t_control);


signals:
	void selectionChanged(FModel* t_model);
};