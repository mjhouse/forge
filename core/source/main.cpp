#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	auto resources = QDir(QDir::cleanPath(app.applicationDirPath() + "/resources"));
	auto stylePath = resources.filePath("stylesheet.qss");

	QFile File(stylePath);
	File.open(QFile::ReadOnly);
	
	app.setStyleSheet(QLatin1String(File.readAll()));

	ForgeWindow window(resources);
	window.build();
	window.show();

	return app.exec();
}