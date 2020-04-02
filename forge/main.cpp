#define __STDC_WANT_SECURE_LIB__ 1

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "ForgeApplication.h"
#include "Resources.h"
#include "BulkLoader.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));
	return app.exec();
}