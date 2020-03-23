#ifndef __FORGEWINDOW_H__
#define __FORGEWINDOW_H__

#include <QtCore/QDir>

#include "IdentifierList.h"
#include "HasIdentifier.h"
#include "Messages.h"
#include "Defines.h"

#include <iostream>

class ForgeControl;

/*! \brief The main 3D window class
 */
class ForgeWindow:  public QWindow, 
					public HasIdentifier,
					public Handler
{
	Q_OBJECT

private:

	QtCamera* m_camera;							/*!< The camera for this 3D window */

	QtForwardRenderer* m_renderer;				/*!< The renderer for this window */

	IdentifierList<ForgeControl> m_controls;	/*!< A collection of currently active child controls */
	
	_method_publish(focusInEvent, QFocusEvent, Channel::Action)
	_method_publish(focusOutEvent, QFocusEvent, Channel::Action)
	_method_publish(mouseMoveEvent, QMouseEvent, Channel::Action)

	void resizeEvent(QResizeEvent* event) override;

	void moveEvent(QMoveEvent* t_event) override;

	void closing(ForgeWindow* t_window);

	void updateControls(QRect& oldRect, QRect& newRect);

public:
	ForgeWindow();
	
	~ForgeWindow();

	void onClick(QMouseEvent* t_event);

	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	void clearParent();

	QtCamera* camera();

	QtForwardRenderer* renderer();
	
	void addControl(ForgeControl* t_control);

	void removeControl(ForgeControl* t_control);

	void onMessage(Channel t_channel, UnknownMessage& t_message);

signals:

};

#endif // __FORGEWINDOW_H__
