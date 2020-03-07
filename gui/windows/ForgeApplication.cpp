#include "ForgeApplication.h"
#include "ForgeMainMenu.h"
#include "ForgeTransformMenu.h"

ForgeApplication::ForgeApplication(int argc, char* argv[])
	: QApplication(argc, argv)
	, inputSettings(new QtInputSettings())
	, frameGraph(new QtFrameGraphNode())
	, renderSettings(new QtRenderSettings())
	, aspectEngine()
	, renderAspect(new QtRenderAspect())
	, inputAspect(new QtInputAspect())
	, logicAspect(new QtLogicAspect())
	, rootEntity(new QtEntity())
	, controller(new QtController())
	, m_selected(nullptr)
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

FModel* ForgeApplication::getSelected()
{
	return this->m_selected;
}

void ForgeApplication::setSelected(FModel* t_model)
{
	this->m_selected = t_model;
}


void ForgeApplication::setActive(ForgeWindow* t_window) {
	if (t_window != nullptr) {
		controller->setCamera(t_window->getCamera());
		inputSettings->setEventSource(t_window);
		container.prioritize(t_window->id());
	}
}

void ForgeApplication::onWindowClose(ForgeWindow* t_window) {

	// clear parent node and framegraph
	t_window->clearParent();

	// remove window from window collection
	container.remove(t_window);

	// if there is another window in the collection
	// set it as active. otherwise, close all controls
	if (container.size() > 0) {
		setActive(container.high());
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

	/*Davids test stuff.*/

	
	auto transformMenu = new ForgeTransformMenu();

	(void)this->connect(transformMenu, &ForgeTransformMenu::exitCommand, this, &ForgeApplication::onExit);
	(void)this->connect(transformMenu, &ForgeTransformMenu::optionsCommand, this, &ForgeApplication::onOptions);

	controls.push_back(transformMenu);
	transformMenu->showAt(100, 100);
}

ForgeWindow* ForgeApplication::newWindow() {
	auto window = new ForgeWindow();

	window->setRenderSource(frameGraph);
	window->setRoot(rootEntity.data());

	(void)this->connect(window, &ForgeWindow::onFocus,
		this, &ForgeApplication::setActive);

	(void)this->connect(window, &ForgeWindow::onClose,
		this, &ForgeApplication::onWindowClose);

	container.add(window);
	setActive(window);
	window->show();
	return window;
}

ForgeWindow* ForgeApplication::findWindow(QPoint t_point) {
	for (auto window : container.priority()) {
		if (window->geometry().contains(t_point)) {
			return window;
		}
	}
	return nullptr;
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