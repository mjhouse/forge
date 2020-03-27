#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModelExtruded.h"

#include <QMouseEvent>

/*! \brief Constructor for the place object widget.
 */
ForgeCreate::ForgeCreate(ForgeWindow* t_parent) 
	: ForgeControl(t_parent,0.85,0.02)
	, m_length(0.5)
	, m_model(nullptr) 
	, m_lengthInput(new QLineEdit())
	, m_placing(false)
{
	this->hasTitle(true);

	auto widget = new QWidget();
	auto layout = new QGridLayout();

	auto deleteButton = new QPushButton("Delete");
	auto createButton = new QPushButton("Create");

	auto objectPicker = new QComboBox();
	objectPicker->addItem("Test #1");
	objectPicker->addItem("Test #2");

	auto lengthLabel = new QLabel("Length:");

	m_lengthInput->setValidator(new QDoubleValidator(this));
	m_lengthInput->setPlaceholderText("N/A");

	layout->addWidget(objectPicker, 0, 0, 1, 0);
	layout->addWidget(lengthLabel, 1, 0);
	layout->addWidget(m_lengthInput, 1, 1);
	
	layout->addWidget(deleteButton, 2, 0);
	layout->addWidget(createButton, 2, 1);

	(void)this->connect(ForgeApplication::instance(), &ForgeApplication::selectionChanged,
		this, &ForgeCreate::updateView);

	(void)this->connect(deleteButton, &QPushButton::pressed,
		this, &ForgeCreate::deleteModel);

	(void)this->connect(createButton, &QPushButton::pressed,
		this, &ForgeCreate::startCreate);

	(void)this->connect(m_lengthInput, &QLineEdit::textEdited,
		this, &ForgeCreate::lengthChanged);

	widget->setLayout(layout);
	this->setCentralWidget(widget);
	this->setTitle("Place Object");
	this->setFixedWidth(120);
}

/*! \brief Update the displayed length when a new
 *		   object is selected.
 */
void ForgeCreate::updateView(FModel* t_model) {
	auto model = dynamic_cast<FModelExtruded*>(t_model);
	if (model != nullptr) {
		m_lengthInput->setText(QString::number(model->length()));
		m_model = model;
	}
	else {
		m_lengthInput->setText("");
		m_model = nullptr;
	}
}

void ForgeCreate::deleteModel() {
	auto model = ForgeApplication::instance()->selected();
	if (model != nullptr) {
		ForgeApplication::instance()->setSelected(nullptr);
		model->unHighlight();
		model->deleteLater();
	}
}

/*! \brief Create a new object.
 */
void ForgeCreate::startCreate() {

	//// -----------------------------------------------------
	//// TEST TEST TEST
	//FCrossSection* cs = new FCrossSection();
	//cs->setPoints({
	//	{-3.0f, 3.0f},
	//	{-3.0f, -3.0f},
	//	{-1.5f, -3.0f},
	//	{-1.5f, -1.5f},
	//	{1.5f, -1.5f},
	//	{1.5f, -3.0f},
	//	{3.0f, -3.0f},
	//	{3.0f, 3.0f},
	//	{1.5f, 3.0f},
	//	{1.5f, 1.5f},
	//	{-1.5f, 1.5f},
	//	{-1.5f, 3.0f}
	//	});

	//cs->setLength(m_length);
	//m_model = new FModelExtruded(cs);
	//// TEST TEST TEST
	//// -----------------------------------------------------

	//ForgeApplication::instance()->render(m_model);
	//ForgeApplication::instance()->setSelected(m_model);
	//m_placing = true;
}

/*! \brief Update the active model when the user
 *		   changes the selection.
 */
void ForgeCreate::lengthChanged(QString t_input) {
	bool ok = false;
	auto l = t_input.toFloat(&ok);
	if (ok) {
		m_length = l;
		if (m_model != nullptr) {
			m_model->setLength(m_length);
		}
	}
}

void ForgeCreate::onMessage(Channel t_channel, UnknownMessage& t_message) {
	ForgeControl::onMessage(t_channel, t_message);
	_route_in(t_channel, t_message, Channel::Action, QMouseEvent*, onMouseMove);
}

void ForgeCreate::onMouseMove(Message<QMouseEvent*>* t_message) {

	auto event  = t_message->value();
	auto parent = controller();

	if (parent == nullptr || m_model == nullptr) {
		m_placing = false;
		return;
	}

	if (m_placing && t_message->sender()->isHandler(parent)) {
		switch (event->type()) {
		case QEvent::Type::MouseButtonRelease:
			finishCreate();
			break;
		case QEvent::Type::MouseMove:
			positionModel(event->pos());
			break;
		}
	}
}

void ForgeCreate::finishCreate() {
	if (m_model != nullptr) {
		ForgeApplication::instance()->setSelected(m_model);
		m_placing = false;
	}
}

void ForgeCreate::positionModel(QPoint t_point) {

	auto parent = controller();
	if (parent == nullptr) return;

	auto camera = parent->camera();
	auto screen = parent->geometry();

	t_point.setX(t_point.x() + screen.left());
	t_point.setY(t_point.y() - screen.top());

	auto view = camera->viewMatrix();
	auto proj = camera->projectionMatrix();

	auto position = m_model->transform()->translation();
	position = position.project(view, proj, screen);

	position.setX(t_point.x());
	position.setY(screen.height() - t_point.y());

	position = position.unproject(view, proj, screen);
	m_model->transform()->setTranslation(position);
}