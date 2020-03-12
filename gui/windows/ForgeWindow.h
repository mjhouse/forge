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

/*! \brief Event filter for window state changes 
 */
class StateEventFilter : public QObject {
	Q_OBJECT
public:
	StateEventFilter(QObject* parent) : QObject(parent) {}

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

	QtCamera* camera;

	QtForwardRenderer* renderer;

	IdentifierList<ForgeControl> m_controls;

	void focusInEvent(QFocusEvent* ev) override;

	void resizeEvent(QResizeEvent* event) override;

public:
	ForgeWindow();
	
	~ForgeWindow();

	void updateControls(QRect& oldRect, QRect& newRect);

	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	void clearParent();

	QtCamera* getCamera();

	void moveEvent(QMoveEvent* t_event) override;

	void changeEvent(QWindowStateChangeEvent* t_event);
	
	void closing(ForgeWindow* t_window);

	void show();

	void addControl(ForgeControl* t_control);

	void removeControl(ForgeControl* t_control);

signals:
	void onFocus(ForgeWindow* window);

	void onClose(ForgeWindow* window);

	void onShow(ForgeWindow* window);
};

#endif // __FORGEWINDOW_H__
