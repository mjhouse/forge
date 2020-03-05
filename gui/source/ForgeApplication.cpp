#include "ForgeApplication.h"
#include "ForgeMainMenu.h"

ForgeApplication::ForgeApplication(int argc, char* argv[])
	: QApplication(argc, argv)
	, windows()
	, inputSettings(new QtInputSettings())
	, frameGraph(new QtFrameGraphNode())
	, renderSettings(new QtRenderSettings())
	, aspectEngine()
	, renderAspect(new QtRenderAspect())
	, inputAspect(new QtInputAspect())
	, logicAspect(new QtLogicAspect())
	, rootEntity(new QtEntity())
	, controller(new QtController())
{
	rootPath = applicationDirPath();
	resourcesPath = QDir(rootPath.filePath("resources"));
	resources::initialize(resources());

	// initialize the default surface formate for all 
	// QWindow and QWindow derived components
	QSurfaceFormat format;
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setDepthBufferSize(24);
	format.setSamples(4);
	format.setStencilBufferSize(8);

	QSurfaceFormat::setDefaultFormat(format);

	// register aspects and set a base framegraph
	aspectEngine.registerAspect(renderAspect);
	aspectEngine.registerAspect(inputAspect);
	aspectEngine.registerAspect(logicAspect);

	renderSettings->setActiveFrameGraph(frameGraph);

	rootEntity->addComponent(renderSettings);
	rootEntity->addComponent(inputSettings);

	aspectEngine.setRootEntity(rootEntity);

	controller->setParent(rootEntity.data());
	controller->setLinearSpeed(50.0f);
	controller->setLookSpeed(100.0f);

	initialize();
}

ForgeApplication* ForgeApplication::instance() {
	return (ForgeApplication*)QApplication::instance();
}

QDir ForgeApplication::root() {
	return this->rootPath;
}

QDir ForgeApplication::resources() {
	return this->resourcesPath;
}

void ForgeApplication::setActive(ForgeWindow* t_window) {
	if (t_window != nullptr) {
		controller->setCamera(t_window->getCamera());
		inputSettings->setEventSource(t_window);
	}
}

void ForgeApplication::onWindowClose(ForgeWindow* t_window) {

	// clear parent node and framegraph
	t_window->clearParent();

	// remove window from window collection
	windows.erase(std::remove_if(windows.begin(), windows.end(),
		[t_window](auto w) {
			return t_window->isWindow(w);
		}),windows.end());

	// if there is another window in the collection
	// set it as active. otherwise, close all controls
	if (windows.size() > 0) {
		setActive(windows.at(0));
	}
	else {
		for (auto control : controls) {
			control->close();
		}
	}
}

void ForgeApplication::initialize() {
	auto window = newWindow();

	auto mainMenu = new ForgeMainMenu();

	(void)this->connect(mainMenu, &ForgeMainMenu::exitCommand, this, &ForgeApplication::onExit);
	(void)this->connect(mainMenu, &ForgeMainMenu::viewCommand, this, &ForgeApplication::onView);
	(void)this->connect(mainMenu, &ForgeMainMenu::placeCommand, this, &ForgeApplication::onPlace);
	(void)this->connect(mainMenu, &ForgeMainMenu::optionsCommand, this, &ForgeApplication::onOptions);


	controls.push_back(mainMenu);

	mainMenu->show();
}

ForgeWindow* ForgeApplication::newWindow() {
	auto window = new ForgeWindow();

	window->setRenderSource(frameGraph);
	window->setRoot(rootEntity.data());

	(void)this->connect(window, &ForgeWindow::onFocus,
		this, &ForgeApplication::setActive);

	(void)this->connect(window, &ForgeWindow::onClose,
		this, &ForgeApplication::onWindowClose);

	windows.push_back(window);
	setActive(window);
	window->show();
	return window;
}

void ForgeApplication::render(FModel* t_model) {
	t_model->setParent(rootEntity.data());
}

void ForgeApplication::onExit(bool t_checked) {
	this->quit();
}

void ForgeApplication::onView(bool t_checked) {
	newWindow();
}

void ForgeApplication::onPlace(bool t_checked) {

}

void ForgeApplication::onOptions(bool t_checked) {

}