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
	auto layout = new QVBoxLayout();
	auto widget = new FWidget();
	
	//positions options
	auto inputs = new QGridLayout();
	
	auto pl = new QLabel("Translation");
	auto pxl = new QLabel("X");
	px->setValidator(new QDoubleValidator(this));
	px->setPlaceholderText("N/A");

	auto pyl = new QLabel("Y");
	py->setValidator(new QDoubleValidator(this));
	py->setPlaceholderText("N/A");

	auto pzl = new QLabel("Z");
	pz->setValidator(new QDoubleValidator(this));
	pz->setPlaceholderText("N/A");

	inputs->addWidget(pl,  0, 0, 1, 2);
	inputs->addWidget(pxl, 1, 0, Qt::AlignRight);
	inputs->addWidget(pyl, 2, 0, Qt::AlignRight);
	inputs->addWidget(pzl, 3, 0, Qt::AlignRight);

	inputs->addWidget(px, 1, 1);
	inputs->addWidget(py, 2, 1);
	inputs->addWidget(pz, 3, 1);

	auto rl  = new QLabel("Rotation");
	auto rxl = new QLabel("X");
	rx->setValidator(new QDoubleValidator(this));
	rx->setPlaceholderText("N/A");

	auto ryl = new QLabel("Y");
	ry->setValidator(new QDoubleValidator(this));
	ry->setPlaceholderText("N/A");

	auto rzl = new QLabel("Z");
	rz->setValidator(new QDoubleValidator(this));
	rz->setPlaceholderText("N/A");

	inputs->addWidget(rl, 4, 0, 1, 2);
	inputs->addWidget(rxl, 5, 0, Qt::AlignRight);
	inputs->addWidget(ryl, 6, 0, Qt::AlignRight);
	inputs->addWidget(rzl, 7, 0, Qt::AlignRight);

	inputs->addWidget(rx, 5, 1);
	inputs->addWidget(ry, 6, 1);
	inputs->addWidget(rz, 7, 1);

	widget->setLayout(inputs);

	(void)this->connect(ForgeApplication::instance(), &ForgeApplication::selectionChanged,
						this, &ForgeTransform::updateView);

	(void)this->connect(px, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(py, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(pz, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(rx, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(ry, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(rz, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	widget->setLayout(layout);
	this->setCentralWidget(widget);
	this->setObjectName("TransformMenu");
	this->setTitle("Move Object");
	this->setFixedWidth(100);
}

void ForgeTransform::updateView()
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

void ForgeTransform::updateModel()
{
	auto selected = ForgeApplication::instance()->getSelected();
	if (selected != nullptr)
	{
		auto p = selected->getTransform();

		auto x = px->text().toFloat();
		auto y = py->text().toFloat();
		auto z = pz->text().toFloat();

		p->setTranslation(QVector3D(x, y, z));
		p->setRotationX(rx->text().toFloat());
		p->setRotationY(ry->text().toFloat());
		p->setRotationZ(rz->text().toFloat());
	}
}