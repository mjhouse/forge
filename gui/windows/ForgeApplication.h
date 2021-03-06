#ifndef __FORGEAPPLICATION_H__
#define __FORGEAPPLICATION_H__

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
#include "Messages.h"
#include "Message.h"

class FCameraController;

class ForgeApplication : public QApplication, public Handler {

	Q_OBJECT

private:
	
	IdentifierList<ForgeWindow> m_windows;		/*!< The collection of all windows */

	IdentifierList<ForgeControl> m_controls;	/*!< The collection of all controls */

	QtInputSettings* m_inputSettings;			/*!< Input control logic */

	QtFrameGraphNode* m_frameGraph;				/*!< The shared framegraph for all windows */

	QtRenderSettings* m_renderSettings;			/*!< Render settings control object */

	QtAspectEngine m_aspectEngine;				/*!< Aspect management engine */

	QtRenderAspect* m_renderAspect;				/*!< Allows render events/configuration */

	QtInputAspect* m_inputAspect;				/*!< Allows input events/configuration */

	QtLogicAspect* m_logicAspect;				/*!< Seems to manage event routing */

	QtEntityPtr m_rootEntity;					/*!< The root entity for the 3D view */

	FCameraController* m_controller;			/*!< The single camera controller */
	
	FModel* m_selected;							/*!< The currently selected model */
	
	ForgeWindow* m_active;						/*!< The currently active window */
	
	void setActive(ForgeWindow* t_window);

	void onWindowClose(Message<QCloseEvent*>* t_message);
	
	void onWindowFocus(Message<QFocusEvent*>* t_message);

	ForgeWindow* newWindow();
	
	void onExit(bool t_checked);

	void onView(bool t_checked);
	
public:

	ForgeApplication(int argc, char* argv[]);

	~ForgeApplication(){}

	static ForgeApplication* instance();

	ForgeWindow* findWindow(QPoint t_point);

	FModel* selected();
	
	void render(FModel* t_model);
		
	void onReassign(Message<ForgeControl*>* t_message);

	void onMessage(Channel t_channel, UnknownMessage& t_message);

signals:
	void selectionChanged(FModel* t_model);

};

#endif // __FORGEAPPLICATION_H__