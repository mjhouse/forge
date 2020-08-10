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
					protected QOpenGLFunctions
{
	Q_OBJECT

private:

	QtCamera* m_camera;							/*!< The camera for this 3D window */

	QtForwardRenderer* m_renderer;				/*!< The renderer for this window */

	IdentifierList<ForgeControl> m_controls;	/*!< A collection of currently active child controls */
	
	QOpenGLContext* m_context;					/*!< The OpenGL context */

	void focusInEvent(QFocusEvent* t_event) override {
		emit gotFocusEvent(this);
	}

	void focusOutEvent(QFocusEvent* t_event) override {
		emit lostFocusEvent(t_event);
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

	void onClose(QCloseEvent* t_event);

	void onClick(QMouseEvent* t_event);

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
	
	friend class CloseEventFilter;
	friend class ClickEventFilter;

signals:

	void onMouseMove(QMouseEvent* t_event);

	void onMouseRelease(QMouseEvent* t_event);

	void onCloseEvent(ForgeWindow* t_window);

	void onClickEvent(QMouseEvent* t_event);

	void gotFocusEvent(ForgeWindow* t_window);

	void lostFocusEvent(QFocusEvent* t_event);

};

Q_DECLARE_METATYPE(QMouseEvent*);
Q_DECLARE_METATYPE(QCloseEvent*);
Q_DECLARE_METATYPE(QFocusEvent*);
Q_DECLARE_METATYPE(ForgeWindow*);

#endif // __FORGEWINDOW_H__
