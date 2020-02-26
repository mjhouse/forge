#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtCore/QDir>

#include "ForgeWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	auto stylePath = QDir(app.applicationDirPath()).filePath("resources/stylesheet.qss");
	QFile File(stylePath);
	File.open(QFile::ReadOnly);
	
	app.setStyleSheet(QLatin1String(File.readAll()));

	ForgeWindow window;
	window.build();
	window.show();

	return app.exec();
}