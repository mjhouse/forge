#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModelExtruded.h"

#include <QMouseEvent>

/*! \brief Constructor for the place object widget.
 */
ForgeCreate::ForgeCreate() 
	: m_length(0.5)
	, m_model(nullptr) 
	, m_lengthInput(new QLineEdit())
	, m_button(new QPushButton("Create"))
	, m_placing(false)
{
	this->hasTitle(true);

	auto widget = new QWidget();
	auto layout = new QGridLayout();

	auto lengthLabel = new QLabel("Length:");

	m_lengthInput->setValidator(new QDoubleValidator(this));
	m_lengthInput->setPlaceholderText("N/A");

	layout->addWidget(lengthLabel, 0, 0);
	layout->addWidget(m_lengthInput, 0, 1);
	layout->addWidget(m_button, 1, 1);

	(void)this->connect(ForgeApplication::instance(), &ForgeApplication::selectionChanged,
		this, &ForgeCreate::updateView);

	(void)this->connect(m_button, &QPushButton::pressed,
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

/*! \brief Create a new object.
 */
void ForgeCreate::startCreate() {

	// -----------------------------------------------------
	// TEST TEST TEST
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

	cs->setLength(m_length);
	m_model = new FModelExtruded(cs);
	// TEST TEST TEST
	// -----------------------------------------------------

	ForgeApplication::instance()->render(m_model);
	ForgeApplication::instance()->setSelected(m_model);
	m_placing = true;
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
	if (auto message = t_message.to<QMouseEvent*>()) {
		if (message->sender() == controller()) {
			qDebug() << message->name();
		}
	}
}


//void ForgeCreate::onParentMouseMove(QPoint t_point) {
//	auto parent = controller();
//	if (m_model == nullptr || parent == nullptr) {
//		m_placing = false;
//	}
//	else if (m_placing) {
//		auto camera = parent->camera();
//		auto screen = parent->geometry();
//
//		t_point.setX(t_point.x() + screen.left());
//		t_point.setY(t_point.y() - screen.top());
//
//		auto view = camera->viewMatrix();
//		auto proj = camera->projectionMatrix();
//
//		auto position = m_model->transform()->translation();
//		position = position.project(view, proj, screen);
//
//		position.setX(t_point.x());
//		position.setY(screen.height() - t_point.y());
//
//		position = position.unproject(view, proj, screen);
//		m_model->transform()->setTranslation(position);
//	}
//}

//void ForgeCreate::onParentMouseClick(QPoint t_point) {
//	m_placing = false;
//}