#include "ForgeCreate.h"
#include "FCrossSection.h"
#include "ForgeApplication.h"
#include "FModelExtruded.h"

ForgeCreate::ForgeCreate() : m_model(nullptr) {
	this->hasTitle(true);

	auto widget = new QWidget();
	auto layout = new QVBoxLayout();
	auto row = new QHBoxLayout();

	auto length = new QLineEdit();
	length->setValidator(new QDoubleValidator(this));
	length->setPlaceholderText("Length");

	button = new QPushButton("Create");
	row->addStretch(1);
	row->addWidget(button);

	layout->addWidget(length);
	layout->addItem(row);

	(void)this->connect(button, &QPushButton::pressed,
		this, &ForgeCreate::startCreate);

	(void)this->connect(length, &QLineEdit::textChanged,
		this, &ForgeCreate::lengthChanged);

	layout->addStretch(1);
	widget->setLayout(layout);
	this->setCentralWidget(widget);
}

void ForgeCreate::cancelCreate() {
	auto k = 0;
}

void ForgeCreate::finishCreate() {
	auto k = 0;
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