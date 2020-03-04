#include <iostream>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QAbstractCameraController>

#include <Qt3DRender/QViewport>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QRenderAspect>
#include <QtGui/QWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DInput/QInputSettings>
#include <Qt3DLogic/QLogicAspect>

#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeApplication.h"
#include "ForgeWindow.h"
#include "Resources.h"
#include "Defines.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));

	app.addWindow(new ForgeWindow());
	app.addWindow(new ForgeWindow());

	app.show();
	return app.exec();
}