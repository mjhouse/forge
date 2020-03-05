#include <QtWidgets/QShortcut>

#include "CommandBase.h"


#define LISTEN(s,r)   (void)this->connect(ForgeRenderer::instance(), &ForgeRenderer::s, this, &Command::r)
#define UNLISTEN(s,r) (void)this->disconnect(ForgeRenderer::instance(), &ForgeRenderer::s, this, &Command::r)

Command* Command::command = nullptr;

TitleButton::TitleButton(QString t_icon) {
	this->setIcon(resources::icon(t_icon));
	this->setObjectName("TitleButton");
};

void TitleBar::build() {
	auto layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
	auto expand_btn = new TitleButton("expand");
	auto close_btn = new TitleButton("close");

	layout->addStretch(1);
	layout->addWidget(expand_btn);
	layout->addWidget(close_btn);

	(void)this->connect(expand_btn, &QPushButton::pressed,
		this, &TitleBar::expandButtonPressed);
	(void)this->connect(close_btn, &QPushButton::pressed,
		this, &TitleBar::closeButtonPressed);

	this->setLayout(layout);
	this->setObjectName("TitleBar");
}

void TitleBar::expandButtonPressed() {
	auto parent = (QDockWidget*)this->parent();
	parent->setFloating(!parent->isFloating());
}

void TitleBar::closeButtonPressed() {
	((QDockWidget*)this->parent())->close();
}

void Command::clearActive() {
	if (command != nullptr) {
		command->unlisten();
		command->onDeactivated();
		command = nullptr;
	}
}

void Command::setActive(Command* t_command) {
	if (command != this) {
		clearActive();
		command = this;
		this->onActivated();
		this->listen();
	}
}

void Command::focusInEvent(QFocusEvent* e) {
	if (command != this) {
		setActive(this);
	}
}

void Command::closeEvent(QCloseEvent* e) {
	QDockWidget::closeEvent(e);
	clearActive();
}

void Command::visibilityEvent(bool t_visible) {
	if (t_visible) {
		setActive(this);
	}
}

void Command::unlisten() {
	for (auto shortcut : shortcuts)
		shortcut->setEnabled(false);

	UNLISTEN(mouseMove, onMove);
	UNLISTEN(mouseRelease, onClick);
}

void Command::listen() {
	for (auto shortcut : shortcuts)
		shortcut->setEnabled(true);

	LISTEN(mouseMove, onMove);
	LISTEN(mouseRelease, onClick);
}

void Command::onDockChanged(bool t_floating) {
	if (t_floating) {
		this->resize(this->sizeHint());
	}
}

Command::Command(QWidget* t_parent)
	: QDockWidget(t_parent)
{
	this->setTitleBarWidget(new TitleBar());
	this->setWidget(new QWidget());

	this->setAllowedAreas(
		Qt::DockWidgetArea::LeftDockWidgetArea |
		Qt::DockWidgetArea::RightDockWidgetArea);

	(void)this->connect(this, &QDockWidget::topLevelChanged,
						this, &Command::onDockChanged);
	
	(void)this->connect(this, &QDockWidget::visibilityChanged,
						this, &Command::visibilityEvent);

	this->setMinimumWidth(100);
	this->setObjectName("Control");
	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

	auto escapeShortcut = new QShortcut(QKeySequence(tr("Esc")),this);
	auto enterShortcut  = new QShortcut(QKeySequence(tr("Enter")), this);

	(void)this->connect(escapeShortcut, &QShortcut::activated,
						this, [this]() { onShortcut(ShortcutKey::EscapeKey); });

	(void)this->connect(enterShortcut, &QShortcut::activated,
						this, [this]() { onShortcut(ShortcutKey::EnterKey); });

	shortcuts.push_back(escapeShortcut);
	shortcuts.push_back(enterShortcut);
}

void Command::onActivated() {

}

void Command::onDeactivated() {

}

void Command::onMove(QMouseEvent* e) {

}

void Command::onClick(QMouseEvent* e) {

}

void Command::onShortcut(ShortcutKey key) {

}
