#ifndef __FORGEWINDOW_H__
#define __FORGEWINDOW_H__

#include <QtCore/QDir>

#include "IdentifierList.h"
#include "HasIdentifier.h"
#include "Defines.h"

#include <iostream>

class ForgeControl;

/*! \brief Event filter for window close events
 */
class CloseEventFilter : public QObject {
	Q_OBJECT
public:
	CloseEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

/*! \brief Event filter for window click events
 */
class ClickEventFilter : public QObject {
	Q_OBJECT
public:
	ClickEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

/*! \brief The main 3D window class
 */
class ForgeWindow:  public QWindow, 
					public HasIdentifier
{
	Q_OBJECT

private:

	QtCamera* m_camera;							/*!< The camera for this 3D window */

	QtForwardRenderer* m_renderer;				/*!< The renderer for this window */

	IdentifierList<ForgeControl> m_controls;	/*!< A collection of currently active child controls */

	void focusInEvent(QFocusEvent* ev) override;

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

signals:
	void onFocus(ForgeWindow* window);

	void onClose(ForgeWindow* window);
};

#endif // __FORGEWINDOW_H__
