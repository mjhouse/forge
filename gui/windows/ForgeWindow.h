#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QForwardRenderer>
#include <QtGui/QWindow>
#include <QtCore/QDir>

#include "HasIdentifier.h"
#include "HasControls.h"
#include "Defines.h"

typedef Qt3DRender::QCamera QtCamera;
typedef Qt3DExtras::QForwardRenderer QtForwardRenderer;
typedef Qt3DRender::QFrameGraphNode QtFrameGraphNode;

using namespace components;

class CloseEventFilter : public QObject {
	Q_OBJECT
public:
	CloseEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

class StateEventFilter : public QObject {
	Q_OBJECT
public:
	StateEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};



class ForgeWindow:  public QWindow, 
					public HasIdentifier, 
					public HasControls 
{
	Q_OBJECT

private:

	QtCamera* camera;

	QtForwardRenderer* renderer;

	void focusInEvent(QFocusEvent* ev) override;

	void resizeEvent(QResizeEvent* event) override;

	//void mouseMoveEvent(QMouseEvent* t_event) override;

public:
	ForgeWindow();
	~ForgeWindow();

	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	void clearParent();

	QtCamera* getCamera();

	void moveEvent(QMoveEvent* t_event) override;

	void changeEvent(QWindowStateChangeEvent* t_event);
	
	void closing(ForgeWindow* t_window);

	void show() {
		QWindow::show();
		QApplication::processEvents();
		emit onShow(this);
	}

signals:
	void onFocus(ForgeWindow* window);

	void onClose(ForgeWindow* window);

	void onShow(ForgeWindow* window);

	//void onMouseMove(QMouseEvent* t_event);

};

