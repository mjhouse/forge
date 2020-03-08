#include "ForgeApplication.h"
#include "ForgeMainMenu.h"
#include "ForgeCreate.h"
#include "ForgeTransform.h"

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
	, controller(new QtOrbitController())
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

	auto objectPicker = new QtObjectPicker;
	rootEntity->addComponent(renderSettings);
	rootEntity->addComponent(inputSettings);
	rootEntity->addComponent(objectPicker);

	aspectEngine.setRootEntity(rootEntity);

	controller->setParent(rootEntity.data());
	controller->setLinearSpeed(50.0f);
	controller->setLookSpeed(100.0f);

	initialize();
	(void)this->connect(objectPicker, &QtObjectPicker::clicked, this, &ForgeApplication::onClick);
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

void ForgeApplication::onClick(Qt3DRender::QPickEvent* t_event)
{
	auto model = (FModel*)t_event->entity();
	setSelected(model);
}

void ForgeApplication::setSelected(FModel* t_model)
{
	if (m_selected != nullptr)
	{
		m_selected->unSelect();
	}

	this->m_selected = t_model;
	m_selected->select();
	emit selectionChanged(t_model);
	//reset(m_selected->getTransform()->translation());
}

void ForgeApplication::reset(QVector3D pivot)
{
	auto camera = controller->camera();
	
	camera->setPosition(pivot + (camera->position() - camera->viewCenter()));
	camera->setViewCenter(pivot);
	camera->setUpVector(QVector3D(0, 0, 1));
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
		for (auto control : m_controls.priority()) {
			control->close();
		}
	}
}

void ForgeApplication::initialize() {
	auto window = newWindow();

	auto mainMenu = new ForgeMainMenu();
	auto createControl = new ForgeCreate();
	auto moveControl = new ForgeTransform();

	(void)this->connect(mainMenu, &ForgeMainMenu::exitCommand, this, &ForgeApplication::onExit);
	(void)this->connect(mainMenu, &ForgeMainMenu::viewCommand, this, &ForgeApplication::onView);
	(void)this->connect(mainMenu, &ForgeMainMenu::launchCommand, this, &ForgeApplication::onLaunch);

	m_controls.add(mainMenu);
	m_controls.add(moveControl);
	m_controls.add(createControl);

	mainMenu->addLauncher(RootMenu::View, "Move", moveControl);
	mainMenu->addLauncher(RootMenu::View, "Create", createControl);

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

void ForgeApplication::onLaunch(int t_id) {
	//transformMenu->showAt(100, 100);
}