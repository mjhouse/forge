#include <iostream>

#include "ForgeApplication.h"
#include "Resources.h"
#include "FModelLine.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));

	/*Davids playground*/

	FLine* zline = new FLine({
		{0, 0, 0},
		{0, 0, 5},
		});

	ForgeApplication::instance()->render(new FModelLine(zline, QColor::fromRgbF(0, 0, 1)));

	FLine* yline = new FLine({
		{0, 0, 0},
		{0, 5, 0},
			});

	ForgeApplication::instance()->render(new FModelLine(yline, QColor::fromRgbF(0, 1, 0)));

	FLine* xline = new FLine({
		{0, 0, 0},
		{5, 0, 0},
		});

	ForgeApplication::instance()->render(new FModelLine(xline, QColor::fromRgbF(1, 0, 0)));

	/*End Davids playground*/

	return app.exec();
}