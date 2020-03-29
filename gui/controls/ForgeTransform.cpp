#include "ForgeTransform.h"
#include "ForgeApplication.h"

/*! \brief The constructor of the transform control.
 */
ForgeTransform::ForgeTransform(ForgeWindow* t_parent)
	: ForgeControl(t_parent,0.87f,0.15f)
	, m_posX(new QLineEdit())
	, m_posY(new QLineEdit())
	, m_posZ(new QLineEdit())
	, m_rotX(new QLineEdit())
	, m_rotY(new QLineEdit())
	, m_rotZ(new QLineEdit())
{
	auto layout = new QVBoxLayout();
	auto widget = new FWidget();
	
	//positions options
	auto inputs = new QGridLayout();
	
	auto pl = new QLabel("Translation");
	auto pxl = new QLabel("X");
	m_posX->setValidator(new QDoubleValidator(this));
	m_posX->setPlaceholderText("N/A");

	auto pyl = new QLabel("Y");
	m_posY->setValidator(new QDoubleValidator(this));
	m_posY->setPlaceholderText("N/A");

	auto pzl = new QLabel("Z");
	m_posZ->setValidator(new QDoubleValidator(this));
	m_posZ->setPlaceholderText("N/A");

	inputs->addWidget(pl,  0, 0, 1, 2);
	inputs->addWidget(pxl, 1, 0, Qt::AlignRight);
	inputs->addWidget(pyl, 2, 0, Qt::AlignRight);
	inputs->addWidget(pzl, 3, 0, Qt::AlignRight);

	inputs->addWidget(m_posX, 1, 1);
	inputs->addWidget(m_posY, 2, 1);
	inputs->addWidget(m_posZ, 3, 1);

	auto rl  = new QLabel("Rotation");
	auto rxl = new QLabel("X");
	m_rotX->setValidator(new QDoubleValidator(this));
	m_rotX->setPlaceholderText("N/A");

	auto ryl = new QLabel("Y");
	m_rotY->setValidator(new QDoubleValidator(this));
	m_rotY->setPlaceholderText("N/A");

	auto rzl = new QLabel("Z");
	m_rotZ->setValidator(new QDoubleValidator(this));
	m_rotZ->setPlaceholderText("N/A");

	inputs->addWidget(rl, 4, 0, 1, 2);
	inputs->addWidget(rxl, 5, 0, Qt::AlignRight);
	inputs->addWidget(ryl, 6, 0, Qt::AlignRight);
	inputs->addWidget(rzl, 7, 0, Qt::AlignRight);

	inputs->addWidget(m_rotX, 5, 1);
	inputs->addWidget(m_rotY, 6, 1);
	inputs->addWidget(m_rotZ, 7, 1);

	widget->setLayout(inputs);

	(void)this->connect(ForgeApplication::instance(), &ForgeApplication::selectionChanged,
						this, &ForgeTransform::updateView);

	(void)this->connect(m_posX, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(m_posY, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(m_posZ, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(m_rotX, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(m_rotY, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	(void)this->connect(m_rotZ, &QLineEdit::textEdited,
		this, &ForgeTransform::updateModel);

	widget->setLayout(layout);
	this->setCentralWidget(widget);
	this->setObjectName("TransformMenu");
	this->setTitle("Move Object");
	this->setFixedWidth(100);
}

/*! \brief When the model selection changes, this callback 
 *		   updates the displayed values.
 */
void ForgeTransform::updateView(FModel* t_model)
{
	if (t_model != nullptr)
	{
		auto p = t_model->transform()->translation();

		m_posX->setText(QString::number(p.x()));
		m_posY->setText(QString::number(p.y()));
		m_posZ->setText(QString::number(p.z()));

		auto r = t_model->transform()->rotation();

		m_rotX->setText(QString::number(t_model->transform()->rotationX()));
		m_rotY->setText(QString::number(t_model->transform()->rotationY()));
		m_rotZ->setText(QString::number(t_model->transform()->rotationZ()));
	}
	else
	{
		m_posX->clear();
		m_posY->clear();
		m_posZ->clear();

		m_rotX->clear();
		m_rotY->clear();
		m_rotZ->clear();
	}
}

/*! \brief When the input values change, this callback
 *		   updates the selected model.
 */
void ForgeTransform::updateModel()
{
	auto selected = ForgeApplication::instance()->selected();
	if (selected != nullptr)
	{
		auto p = selected->transform();

		auto x = m_posX->text().toFloat();
		auto y = m_posY->text().toFloat();
		auto z = m_posZ->text().toFloat();

		p->setTranslation(QVector3D(x, y, z));
		p->setRotationX(m_rotX->text().toFloat());
		p->setRotationY(m_rotY->text().toFloat());
		p->setRotationZ(m_rotZ->text().toFloat());
	}
}