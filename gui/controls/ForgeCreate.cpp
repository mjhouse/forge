#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModel.h"
#include "Selection.hpp"

#include <QMouseEvent>

#define _distance(a,b)				 \
	std::sqrtf(						 \
		std::powf(b.x() - a.x(),2) + \
		std::powf(b.y() - a.y(),2) + \
		std::powf(b.z() - a.z(),2)	 \
	)								 \

/*! \brief Constructor for the place object widget.
 */
ForgeCreate::ForgeCreate(ForgeWindow* t_parent) 
	: ForgeControl(t_parent,0.85f,0.02f)
	, m_length(0.5f)
	, m_model(nullptr) 
	, m_lengthInput(new QLineEdit())
	, m_loader()
	, m_symbol(nullptr)
	, m_mode(PlacementType::None)
{
	m_loader.load(resources::data("basev0.1.json"));
	this->hasTitle(true);

	auto widget = new QWidget();
	auto layout = new QGridLayout();

	auto deleteButton = new QPushButton("Delete");
	auto createButton = new QPushButton("Create");

	auto objectPicker = new QComboBox();
	
	for (auto& p : m_loader.symbols()) {
		auto name = p.second->property<std::string>("name");
		objectPicker->addItem(QString::fromStdString(name));
	}

	objectPicker->setCurrentIndex(0);
	auto symbolName = objectPicker->currentText();
	m_symbol = m_loader.getName(symbolName.toStdString());

	auto lengthLabel = new QLabel("Length:");

	m_lengthInput->setValidator(new QDoubleValidator(this));
	m_lengthInput->setPlaceholderText("none");

	layout->addWidget(objectPicker, 0, 0, 1, 0);
	layout->addWidget(lengthLabel, 1, 0);
	layout->addWidget(m_lengthInput, 1, 1);
	
	layout->addWidget(deleteButton, 2, 0);
	layout->addWidget(createButton, 2, 1);

	(void)this->connect(Selection::get(), &Selection::selectionChanged,
		this, &ForgeCreate::updateView);

	(void)this->connect(deleteButton, &QPushButton::pressed,
		this, &ForgeCreate::deleteModel);

	(void)this->connect(createButton, &QPushButton::pressed,
		this, &ForgeCreate::updateModel);

	(void)this->connect(m_lengthInput, &QLineEdit::textEdited,
		this, &ForgeCreate::lengthChanged);

	(void)this->connect(objectPicker, &QComboBox::currentTextChanged,
		this, &ForgeCreate::selectionChanged);

	widget->setLayout(layout);
	this->setCentralWidget(widget);
	this->setTitle("Place Object");
	this->setFixedWidth(120);
}

/*! \brief Update the displayed length when a new
 *		   object is selected.
 */
void ForgeCreate::updateView() {
	auto models = Selection::get()->selection();
	if (models.size() == 1) {
		auto model  = models.front();
		auto length = model->symbol()->property<float>("length");
		m_lengthInput->setText(QString::number(length));
		m_lengthInput->setPlaceholderText("none");
	}
	else if (models.size() == 0) {
		m_lengthInput->setText("");
		m_lengthInput->setPlaceholderText("none");
	}
	else {
		auto length = models.front()->symbol()->property<float>("length");
		if (std::all_of(models.begin(), models.end(), 
			[length](auto m) {
				auto l = m->symbol()->property<float>("length");
				return l == length;
			})) {
			m_lengthInput->setText(QString::number(length));
			m_lengthInput->setPlaceholderText("none");
		}
		else {
			m_lengthInput->setText("");
			m_lengthInput->setPlaceholderText("mixed");
		}
	}
}

/*! \brief Delete the currently selected model.
 */
void ForgeCreate::deleteModel() {
	auto models = Selection::get()->selection();
	Selection::get()->clear();
	for (auto model : models) {
		model->deleteLater();
	}
}

void ForgeCreate::updateModel() {
	if (m_symbol == nullptr) return;

	switch (m_mode) {
		case PlacementType::None:
			m_model = new FModel(m_symbol->copy());
			ForgeApplication::instance()->render(m_model);
			m_mode = PlacementType::Start;
			break;
		case PlacementType::Start:
			m_mode = PlacementType::End;
			break;
		case PlacementType::End:
			m_mode = PlacementType::None;
			m_model = nullptr;
			break;
	}
}

/*! \brief Update the active model when the user
 *		   changes the selection.
 */
void ForgeCreate::lengthChanged(QString t_input) {
	bool ok = false;
	auto length = t_input.toFloat(&ok);
	if (ok) {
		auto models = Selection::get()->selection();
		for (auto model : models) {
			model->symbol()->setProperty("length", length);
		}
	}
}

void ForgeCreate::selectionChanged(const QString& t_input) {
	m_symbol = m_loader.getName(t_input.toStdString());
}

void ForgeCreate::onMessage(Channel t_channel, UnknownMessage& t_message) {
	ForgeControl::onMessage(t_channel, t_message);
	_route_in(t_channel, t_message, Channel::Action, QMouseEvent*, onMouseMove);
}

void ForgeCreate::onMouseMove(Message<QMouseEvent*>* t_message) {

	auto event  = t_message->value();
	auto parent = controller();

	if (parent == nullptr || m_model == nullptr) {
		m_mode = PlacementType::None;
		return;
	}

	if (t_message->sender()->isHandler(parent)) {
		if (event->type() == QEvent::Type::MouseButtonRelease &&
			m_mode != PlacementType::None) {
			updateModel(); // update placement state
		}
		else if (event->type() == QEvent::Type::MouseMove) {
			moveModel(event->pos()); // update placement
		}
	}
}

void ForgeCreate::moveModel(QPoint t_point) {
	switch (m_mode) {
	case PlacementType::Start:
		positionModel(t_point);
		break;
	case PlacementType::End:
		extrudeModel(t_point);
		break;
	}
}

void ForgeCreate::extrudeModel(QPoint t_point) {
	auto parent = controller();
	if (parent == nullptr || m_model == nullptr) 
		return;

	auto camera = parent->camera();
	auto screen = parent->geometry();

	t_point.setX(t_point.x() + screen.left());
	t_point.setY(t_point.y() - screen.top());

	auto view = camera->viewMatrix();
	auto proj = camera->projectionMatrix();

	auto position = m_current;
	position = position.project(view, proj, screen);

	position.setX(t_point.x());
	position.setY(screen.height() - t_point.y());

	position = position.unproject(view, proj, screen);

	auto d = _distance(m_current, position);
	m_model->symbol()->setProperty("length", d);

	// TEST
	auto transform = m_model->transform();
	auto rotation = transform->rotation();

	auto pose = (position - m_current).normalized();
	rotation = QQuaternion::fromDirection(pose,pose);

	transform->setRotation(rotation);

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
	m_current = position;
}