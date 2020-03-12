#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModelExtruded.h"

/*! \brief Constructor for the place object widget.
 */
ForgeCreate::ForgeCreate() 
	: m_length(0.5)
	, m_model(nullptr) 
	, m_lengthInput(new QLineEdit())
	, m_button(new QPushButton("Create"))
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
void ForgeCreate::updateView() {
	auto selected = ForgeApplication::instance()->getSelected();
	auto model = dynamic_cast<FModelExtruded*>(selected);
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