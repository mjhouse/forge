#include "ForgeTransform.h"
#include "ForgeApplication.h"

inline QMenu* ForgeTransform::bind(QMenuBar* t_menu, const char* t_name) {
	auto menu = new QMenu(tr(t_name), this);
	t_menu->addMenu(menu);
	return menu;
}

inline void ForgeTransform::bind(QMenu* t_menu, const char* t_name, void(ForgeTransform::*t_callback)(bool)) {
	(void)this->connect(t_menu->addAction(tr(t_name)), &QAction::triggered,
						this, t_callback);
}

ForgeTransform::ForgeTransform() 
	: px(new QLineEdit())
	, py(new QLineEdit())
	, pz(new QLineEdit())
	, rx(new QLineEdit())
	, ry(new QLineEdit())
	, rz(new QLineEdit())
{
	//this->hasTitle(false);

	auto layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	//positions options
	auto positions = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

	px->setValidator(new QDoubleValidator(this));
	px->setPlaceholderText("PositionX");

	py->setValidator(new QDoubleValidator(this));
	py->setPlaceholderText("PositionY");

	pz->setValidator(new QDoubleValidator(this));
	pz->setPlaceholderText("PositionZ");
	positions->addWidget(px);
	positions->addWidget(py);
	positions->addWidget(pz);	

	auto positionswidget = new FWidget();
	positionswidget->setLayout(positions);

	//rotations options
	auto rotations = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

	rx->setValidator(new QDoubleValidator(this));
	rx->setPlaceholderText("RotationX");

	ry->setValidator(new QDoubleValidator(this));
	ry->setPlaceholderText("RotationY");

	rz->setValidator(new QDoubleValidator(this));
	rz->setPlaceholderText("RotationZ");

	rotations->addWidget(rx);
	rotations->addWidget(ry);
	rotations->addWidget(rz);	

	auto rotationsswidget = new FWidget();
	rotationsswidget->setLayout(rotations);

	// Settings Menu
	auto s = bind(menu, "Settings");
	bind(s, "Options", &ForgeTransform::optionsCommand);
	
	

	auto proptions = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

	//QPushButton* get_button = new QPushButton("Update", this);
	//proptions->addWidget(get_button);

	//this->connect(get_button, &QPushButton::clicked, this, &ForgeTransform::onChange);

	this->connect(ForgeApplication::instance(), &ForgeApplication::selectionChanged, this, &ForgeTransform::onChange);

	QPushButton* set_button = new QPushButton("Set", this);
	proptions->addWidget(set_button);

	this->connect(set_button, &QPushButton::clicked, this, &ForgeTransform::onSet);

	auto translationoptionsswidget = new FWidget();
	translationoptionsswidget->setLayout(proptions);
	

	layout->addWidget(menu);
	layout->addWidget(positionswidget);
	layout->addWidget(rotationsswidget);
	layout->addWidget(translationoptionsswidget);
	//layout->addWidget(get_button);
	layout->addStretch(1);

	//widget->setDrag(true);
	//widget->setDragTarget(this);
	widget->setLayout(layout);

	//this->setHandle(widget);
	this->setCentralWidget(widget);
	this->setObjectName("TransformMenu");

}

void ForgeTransform::onChange()
{
	auto selected = ForgeApplication::instance()->getSelected();
	if (selected != nullptr)
	{
		auto p = selected->getTransform()->translation();

		px->setText(QString::number(p.x()));
		py->setText(QString::number(p.y()));
		pz->setText(QString::number(p.z()));

		auto r = selected->getTransform()->rotation();

		rx->setText(QString::number(selected->getTransform()->rotationX()));
		ry->setText(QString::number(selected->getTransform()->rotationY()));
		rz->setText(QString::number(selected->getTransform()->rotationZ()));
	}
	else
	{
		px->clear();
		py->clear();
		pz->clear();

		rx->clear();
		ry->clear();
		rz->clear();
	}
}

void ForgeTransform::onSet(bool checked)
{
	auto selected = ForgeApplication::instance()->getSelected();
	if (selected != nullptr)
	{
		auto p = selected->getTransform();
		p->setTranslation(*new QVector3D(px->text().toFloat(), py->text().toFloat(), pz->text().toFloat()));
		//p->setRotation(*new QQuaternion(rx->text().toFloat(), ry->text().toFloat(), rz->text().toFloat(), 0));
		p->setRotationX(rx->text().toFloat());
		p->setRotationY(ry->text().toFloat());
		p->setRotationZ(rz->text().toFloat());
	}
}