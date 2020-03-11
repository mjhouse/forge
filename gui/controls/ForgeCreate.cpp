#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModelExtruded.h"

ForgeCreate::ForgeCreate() 
	: m_model(nullptr) 
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
	this->setTitle("Create Object");
	this->setFixedWidth(120);
}

void ForgeCreate::onMouseMove(QMouseEvent* t_event) {

}

void ForgeCreate::startCreate() {
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

	cs->setLength(length);
	m_model = new FModelExtruded(cs);

	ForgeApplication::instance()->render(m_model);
	ForgeApplication::instance()->setSelected(m_model);
}

void ForgeCreate::lengthChanged(QString t_input) {
	bool ok = false;
	auto l = t_input.toFloat(&ok);
	if (ok) {
		length = l;
		if (m_model)
			m_model->setLength(length);
	}
}

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