#include <iostream>

#include "ForgeApplication.h"
#include "Resources.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));
	return app.exec();
}