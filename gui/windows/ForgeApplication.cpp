#include "ForgeApplication.h"
#include "ForgeMainMenu.h"
#include "ForgeCreate.h"
#include "ForgeTransform.h"
#include "ForgeControl.h"
#include "Messages.h"
#include "Message.h"

#include <Qt3DRender/QMultiSampleAntiAliasing>
#include <Qt3DRender/QDepthTest>

/* \brief Constructor and main entry for the application.
 */
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
	, m_selected(nullptr)
	, m_active(nullptr)
{
	// subscribe to channels
	_subscribe(Channel::Action);
	_subscribe(Channel::Reassign);

	// route events to channels
	_event_publish(ForgeApplication::applicationStateChanged, Channel::Action);

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
	m_aspectEngine.setRootEntity(m_rootEntity);

	m_controller->setParent(m_rootEntity.data());
	m_controller->setLinearSpeed(50.0f);
	m_controller->setLookSpeed(100.0f);

	// set up initial windows and controls
	auto window = newWindow();

	auto mainMenu = new ForgeMainMenu(window);
	auto createControl = new ForgeCreate(window);
	auto moveControl = new ForgeTransform(window);

	(void)this->connect(mainMenu, &ForgeMainMenu::exitCommand, this, &ForgeApplication::onExit);
	(void)this->connect(mainMenu, &ForgeMainMenu::viewCommand, this, &ForgeApplication::onView);

	m_controls.add(mainMenu);
	m_controls.add(moveControl);
	m_controls.add(createControl);

	mainMenu->addLauncher(RootMenu::View, "Move", moveControl);
	mainMenu->addLauncher(RootMenu::View, "Create", createControl);

	mainMenu->show();
}

/* \brief Set a window as active (respond to events from the window)
 */
void ForgeApplication::setActive(ForgeWindow* t_window) {
	if (t_window != nullptr && !t_window->is(m_active)) {
		m_inputSettings->setEventSource(t_window);
		m_controller->setCamera(t_window->camera());
		m_windows.prioritize(t_window->id());
		m_active = t_window;
	}
}

/* \brief Clean up when a 3D window closes.
 */
void ForgeApplication::onWindowClose(Message<QCloseEvent*>* t_message) {
	auto window = (ForgeWindow*)t_message->sender();

	// clear parent node and framegraph
	window->clearParent();

	// remove window from window collection
	m_windows.remove(window);

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

/* \brief Create and configure a new window.
 */
ForgeWindow* ForgeApplication::newWindow() {
	auto window = new ForgeWindow();

	window->setRenderSource(m_frameGraph);
	window->setRoot(m_rootEntity.data());

	//(void)this->connect(window, &ForgeWindow::onFocus,
	//	this, &ForgeApplication::setActive);

	//(void)this->connect(window, &ForgeWindow::onClose,
	//	this, &ForgeApplication::onWindowClose);

	m_windows.add(window);
	setActive(window);
	window->show();
	return window;
}

/* \brief On mainmenu -> "Exit" command, clean up and close.
 */
void ForgeApplication::onExit(bool t_checked) {
	this->quit();
}

/* \brief On mainmenu -> "3D Window".
 */
void ForgeApplication::onView(bool t_checked) {
	newWindow();
}

/* \brief Get the ForgeApplication instance.
 */
ForgeApplication* ForgeApplication::instance() {
	return (ForgeApplication*)QApplication::instance();
}

/* \brief Get the path to the root directory.
 */
QDir ForgeApplication::root() {
	return this->m_rootPath;
}

/* \brief Get the path to the resources directory.
 */
QDir ForgeApplication::resources() {
	return this->m_resourcesPath;
}

/* \brief Find a window that contains a point.
 */
ForgeWindow* ForgeApplication::findWindow(QPoint t_point) {
	for (auto window : m_windows.priority()) {
		if (window->geometry().contains(t_point)) {
			return window;
		}
	}
	return nullptr;
}

/* \brief Get the currently selected FModel.
 */
FModel* ForgeApplication::selected()
{
	return this->m_selected;
}

/* \brief Set the selected FModel.
 */
void ForgeApplication::setSelected(FModel* t_model)
{
	if (t_model == m_selected)
		return;

	if (t_model == nullptr) {
		m_selected = nullptr;
		emit selectionChanged(t_model);
		return;
	}
	else {
		t_model->highlight();
	}

	if (!t_model->selectable())
		return;

	if (m_selected != nullptr)
		m_selected->unHighlight();

	m_selected = t_model;
	emit selectionChanged(t_model);
}

/* \brief Display a new FModel.
 */
void ForgeApplication::render(FModel* t_model) {
	t_model->setParent(m_rootEntity.data());
}

/* \brief Reassign a control to a new parent.
 */
void ForgeApplication::onReassign(Message<ForgeControl*>* t_message) {
	auto control = t_message->value();
	auto parent  = control->controller();
	if (parent == nullptr) {
		if(control != nullptr)
			control->close();
		return;
	}

	for (auto window : m_windows.priority()) {
		if (!window->is(parent)) {
			control->setControlled(window);
			return;
		}
	}

	control->close();
}

void ForgeApplication::onMessage(Channel t_channel, UnknownMessage& t_message) {
	_route_in(t_channel, t_message, Channel::Action, QCloseEvent*, onWindowClose);
	_route_in(t_channel, t_message, Channel::Reassign, ForgeControl*, onReassign);
}