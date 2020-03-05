#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QForwardRenderer>
#include <QtGui/QWindow>
#include <QtCore/QDir>

#include "FCrossSection.h"
#include "Config.h"

typedef Qt3DRender::QCamera QtCamera;
typedef Qt3DExtras::QForwardRenderer QtForwardRenderer;
typedef Qt3DRender::QFrameGraphNode QtFrameGraphNode;

class CloseEventFilter : public QObject {
	Q_OBJECT
public:
	CloseEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

class ForgeWindow: public QWindow {
	Q_OBJECT

private:
	
	static int count;

	int id;

	QtCamera* camera;

	QtForwardRenderer* renderer;

	void focusInEvent(QFocusEvent* ev) override;

	void resizeEvent(QResizeEvent* event) override;

public:
	ForgeWindow();
	~ForgeWindow();

	void setRenderSource(QtFrameGraphNode* t_framegraph);

	void setRoot(QtEntity* t_root);
	
	bool isWindow(ForgeWindow* t_window);

	void clearParent();

	QtCamera* getCamera();

signals:
	void onFocus(ForgeWindow* window);

	void onClose(ForgeWindow* window);

};

