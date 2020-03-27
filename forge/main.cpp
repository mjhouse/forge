#include <iostream>

#include "ForgeApplication.h"
#include "Resources.h"

#include "BulkLoader.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));

	auto bl = new BulkLoader();
	bl->load(resources::data("H_Test.json"));

	qDebug() << bl->size();

	return app.exec();
}