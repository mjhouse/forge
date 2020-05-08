#ifndef __FORGEWINDOW_H__
#define __FORGEWINDOW_H__

#include <QtCore/QDir>
#include <QOpenGLFunctions>

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
					public Handler,
					protected QOpenGLFunctions
{
	Q_OBJECT

private:

	QtCamera* m_camera;							/*!< The camera for this 3D window */

	QtForwardRenderer* m_renderer;				/*!< The renderer for this window */

	IdentifierList<ForgeControl> m_controls;	/*!< A collection of currently active child controls */
	
	QOpenGLContext* m_context;					/*!< The OpenGL context */

	void focusInEvent(QFocusEvent* t_event) override {
		Messages::instance()->publish(this, Channel::Action, t_event);
	}

	void focusOutEvent(QFocusEvent* t_event) override {
		Messages::instance()->publish(this, Channel::Action, t_event);
	}

	void mouseMoveEvent(QMouseEvent* t_event) override {
		emit onMouseMove(t_event);
	}

	void mouseReleaseEvent(QMouseEvent* t_event) override {
		emit onMouseRelease(t_event);
	}

	void resizeEvent(QResizeEvent* event) override;

	void moveEvent(QMoveEvent* t_event) override;
	
	void updateControls(QRect& oldRect, QRect& newRect);

	void onWindowClose(Message<QCloseEvent*>* t_message);

public:
	ForgeWindow();
	
	~ForgeWindow();
	
	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	void clearParent();

	QtCamera* camera();

	QtForwardRenderer* renderer();
	
	void addControl(ForgeControl* t_control);

	void removeControl(ForgeControl* t_control);

	void onMessage(Channel t_channel, UnknownMessage& t_message);

signals:

	void onMouseMove(QMouseEvent* t_event);

	void onMouseRelease(QMouseEvent* t_event);

};

Q_DECLARE_METATYPE(QMouseEvent*);

#endif // __FORGEWINDOW_H__
