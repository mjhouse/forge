#include "ForgeApplication.h"
#include "ForgeMainMenu.h"
#include "ForgeCreate.h"
#include "ForgeTransform.h"
#include "ForgeControl.h"

#include <Qt3DRender/QMultiSampleAntiAliasing>
#include <Qt3DRender/QDepthTest>

ForgeApplication::ForgeApplication(int argc, char* argv[])
	: QApplication(argc, argv)
	, m_rootPath()
	, m_resourcesPath()
	, m_windows()
	, m_controls()
	, m_inputSettings(new QtInputSettings())
	, m_frameGraph(new QtFrameGraphNode())
	, m_renderSettings(new QtRenderSettings())
	, m_aspectEngine()
	, m_renderAspect(new QtRenderAspect())
	, m_inputAspect(new QtInputAspect())
	, m_logicAspect(new QtLogicAspect())
	, m_rootEntity(new QtEntity())
	, m_controller(nullptr)
	, m_picker(new QtObjectPicker)
	, m_selected(nullptr)
{
	m_rootPath = applicationDirPath();
	m_resourcesPath = QDir(m_rootPath.filePath("resources"));
	resources::initialize(resources());

	// needs to be created after resources are initialized
	m_controller = new FCameraController();

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
	m_aspectEngine.registerAspect(m_renderAspect);
	m_aspectEngine.registerAspect(m_inputAspect);
	m_aspectEngine.registerAspect(m_logicAspect);
	
	m_renderSettings->setActiveFrameGraph(m_frameGraph);
	m_renderSettings->pickingSettings()->setPickMethod(
		Qt3DRender::QPickingSettings::TrianglePicking);

	m_rootEntity->addComponent(m_renderSettings);
	m_rootEntity->addComponent(m_inputSettings);
	m_rootEntity->addComponent(m_picker);
	
	m_aspectEngine.setRootEntity(m_rootEntity);

	m_controller->setParent(m_rootEntity.data());
	m_controller->setLinearSpeed(50.0f);
	m_controller->setLookSpeed(100.0f);

	initialize();
	(void)this->connect(m_picker, &QtObjectPicker::clicked, this, &ForgeApplication::onClick);
}

void ForgeApplication::initialize() {
	auto window = newWindow();

	auto mainMenu = new ForgeMainMenu();
	auto createControl = new ForgeCreate();
	auto moveControl = new ForgeTransform();

	(void)this->connect(mainMenu, &ForgeMainMenu::exitCommand, this, &ForgeApplication::onExit);
	(void)this->connect(mainMenu, &ForgeMainMenu::viewCommand, this, &ForgeApplication::onView);

	m_controls.add(mainMenu);
	m_controls.add(moveControl);
	m_controls.add(createControl);

	mainMenu->addLauncher(RootMenu::View, "Move", moveControl);
	mainMenu->addLauncher(RootMenu::View, "Create", createControl);

	mainMenu->show();
}

void ForgeApplication::setActive(ForgeWindow* t_window) {
	if (t_window != nullptr) {
		m_controller->setCamera(t_window->camera());
		m_inputSettings->setEventSource(t_window);
		m_windows.prioritize(t_window->id());
	}
}

void ForgeApplication::onWindowClose(ForgeWindow* t_window) {

	// clear parent node and framegraph
	t_window->clearParent();

	// remove window from window collection
	m_windows.remove(t_window);

	// if there is another window in the collection
	// set it as active.
	if (m_windows.size() > 0) {
		setActive(m_windows.high());
	}
	else {
		for (auto child : m_controls.priority()) {
			child->close();
		}
	}
}

ForgeWindow* ForgeApplication::newWindow() {
	auto window = new ForgeWindow();

	window->setRenderSource(m_frameGraph);
	window->setRoot(m_rootEntity.data());

	(void)this->connect(window, &ForgeWindow::onFocus,
		this, &ForgeApplication::setActive);

	(void)this->connect(window, &ForgeWindow::onClose,
		this, &ForgeApplication::onWindowClose);

	m_windows.add(window);
	setActive(window);
	window->show();
	return window;
}

void ForgeApplication::onClick(QtPickEvent* t_event)
{
	auto model = (FModel*)t_event->entity();
	if (model != nullptr)
	{
		setSelected(model);
	}
}

void ForgeApplication::onExit(bool t_checked) {
	this->quit();
}

void ForgeApplication::onView(bool t_checked) {
	newWindow();
}

ForgeApplication* ForgeApplication::instance() {
	return (ForgeApplication*)QApplication::instance();
}

QDir ForgeApplication::root() {
	return this->m_rootPath;
}

QDir ForgeApplication::resources() {
	return this->m_resourcesPath;
}

ForgeWindow* ForgeApplication::findWindow(QPoint t_point) {
	for (auto window : m_windows.priority()) {
		if (window->geometry().contains(t_point)) {
			return window;
		}
	}
	return nullptr;
}

FModel* ForgeApplication::selected()
{
	return this->m_selected;
}

void ForgeApplication::setSelected(FModel* t_model)
{
	if (!t_model->selectable())
		return;

	if (m_selected != nullptr)
		m_selected->unHighlight();

	m_selected = t_model;
	m_selected->highlight();
	emit selectionChanged(t_model);
}

void ForgeApplication::render(FModel* t_model) {
	t_model->setParent(m_rootEntity.data());
}

void ForgeApplication::reassign(ForgeWindow* t_parent, ForgeControl* t_control) {
	if (t_parent == nullptr) {
		if(t_control != nullptr)
			t_control->close();
		return;
	}

	for (auto window : m_windows.priority()) {
		if (!window->is(t_parent)) {
			t_control->setControlled(window);
			return;
		}
	}

	t_control->close();
}