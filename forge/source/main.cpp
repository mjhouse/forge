#include <iostream>

#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeApplication.h"
#include "ForgeWindow.h"
#include "Resources.h"
#include "Defines.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);

	resources::initialize(app.resources());
	app.setStyleSheet(resources::theme("stylesheet"));

	ForgeWindow window;
	window.build();
	window.show();

	return app.exec();
}