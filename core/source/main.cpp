#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeWindow.h"
#include "Resources.h"
#include "Defines.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	resources::initialize(QDir::cleanPath(app.applicationDirPath() + "/resources"));
	app.setStyleSheet(resources::theme("stylesheet"));

	ForgeWindow window;
	window.build();
	window.show();

	return app.exec();
}