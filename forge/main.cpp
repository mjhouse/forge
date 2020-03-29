#define __STDC_WANT_SECURE_LIB__ 1

#include <iostream>

#include "ForgeApplication.h"
#include "Resources.h"
#include "FModelExtruded.h"
#include "BulkLoader.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));
	return app.exec();
}