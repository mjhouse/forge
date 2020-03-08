#include <iostream>

#include "ForgeApplication.h"
#include "Resources.h"
#include "FModel.h"

int main(int argc, char* argv[])
{
	ForgeApplication app(argc, argv);
	app.setStyleSheet(resources::theme("stylesheet"));
	
	FCrossSection* cs = new FCrossSection({
	{-3.0f, 3.0f},
	{-3.0f, -3.0f},
	{-1.5f, -3.0f},
	{-1.5f, -1.5f},
	{1.5f, -1.5f},
	{1.5f, -3.0f},
	{3.0f, -3.0f},
	{3.0f, 3.0f},
	{1.5f, 3.0f},
	{1.5f, 1.5f},
	{-1.5f, 1.5f},
	{-1.5f, 3.0f}
		});

	cs->setLength(0.25);
	auto model = new FModel(cs);
	auto model2 = new FModel(cs);
	app.render(model);
	app.render(model2);
	return app.exec();
}