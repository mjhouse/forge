#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QForwardRenderer>
#include <QtGui/QWindow>
#include <QtCore/QDir>

#include "HasIdentifier.h"
#include "Defines.h"

class ForgeControl;

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

class ForgeWindow: public QWindow, public HasIdentifier {
	Q_OBJECT

private:

	std::map<int,ForgeControl*> controls;

	QtCamera* camera;

	QtForwardRenderer* renderer;

	void focusInEvent(QFocusEvent* ev) override;

	void resizeEvent(QResizeEvent* event) override;

public:
	ForgeWindow();
	~ForgeWindow();

	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	void clearParent();

	QtCamera* getCamera();

	void addControl(ForgeControl* t_control);

	void removeControl(ForgeControl* t_control);

	void moveEvent(QMoveEvent* t_event) override;

signals:
	void onFocus(ForgeWindow* window);

	void onClose(ForgeWindow* window);

};

