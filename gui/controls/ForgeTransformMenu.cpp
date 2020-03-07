#include "ForgeTransformMenu.h"

inline QMenu* ForgeTransformMenu::bind(QMenuBar* t_menu, const char* t_name) {
	auto menu = new QMenu(tr(t_name), this);
	t_menu->addMenu(menu);
	return menu;
}

inline void ForgeTransformMenu::bind(QMenu* t_menu, const char* t_name, void(ForgeTransformMenu::*t_callback)(bool)) {
	(void)this->connect(t_menu->addAction(tr(t_name)), &QAction::triggered,
						this, t_callback);
}

ForgeTransformMenu::ForgeTransformMenu() {
	//this->hasTitle(false);

	auto layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
	auto widget = new FWidget();
	auto menu   = new QMenuBar();

	//positions options
	auto positions = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto px = new QLineEdit();
	px->setValidator(new QDoubleValidator(this));
	px->setPlaceholderText("PositionX");
	auto py = new QLineEdit();
	py->setValidator(new QDoubleValidator(this));
	py->setPlaceholderText("PositionY");
	auto pz = new QLineEdit();
	pz->setValidator(new QDoubleValidator(this));
	pz->setPlaceholderText("PositionZ");
	positions->addWidget(px);
	positions->addWidget(py);
	positions->addWidget(pz);	

	auto positionswidget = new FWidget();
	positionswidget->setLayout(positions);

	//rotations options
	auto rotations = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto rx = new QLineEdit();
	rx->setValidator(new QDoubleValidator(this));
	rx->setPlaceholderText("RotationX");
	auto ry = new QLineEdit();
	ry->setValidator(new QDoubleValidator(this));
	ry->setPlaceholderText("RotationY");
	auto rz = new QLineEdit();
	rz->setValidator(new QDoubleValidator(this));
	rz->setPlaceholderText("RotationZ");
	rotations->addWidget(rx);
	rotations->addWidget(ry);
	rotations->addWidget(rz);	

	auto rotationsswidget = new FWidget();
	rotationsswidget->setLayout(rotations);

	// Settings Menu
	auto s = bind(menu, "Settings");
	bind(s, "Options", &ForgeTransformMenu::optionsCommand);

	layout->addWidget(menu);
	layout->addWidget(positionswidget);
	layout->addWidget(rotationsswidget);
	layout->addStretch(1);

	//widget->setDrag(true);
	//widget->setDragTarget(this);
	widget->setLayout(layout);

	//this->setHandle(widget);
	this->setCentralWidget(widget);
	this->setObjectName("TransformMenu");

}

void onChange()
{

}