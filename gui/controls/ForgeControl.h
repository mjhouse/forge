#ifndef __FORGECONTROL_H__
#define __FORGECONTROL_H__

#include <QtWidgets/QDialog>

#include "ForgeTitleBar.h"
#include "IsControl.h"

class ForgeWindow;

enum class WindowSide {
	None,
	TopRight,
	BottomRight,
	BottomLeft,
	TopLeft
};

class ForgeControl : public QDialog, public components::HasIdentifier {
private:

	ForgeTitleBar* m_title;

	QWidget* m_body;

	FWidget* m_handle;

	bool m_hasTitle;

	WindowSide m_side;
	
	QVector2D m_anchor;
	
	ForgeWindow* m_parent;
	
	bool m_persistent;

	QPoint positionWithin(QRect& t_parent, QRect& t_child);

	void moveEvent(QMoveEvent* t_event) override;

	void findSide(QRect& t_rect);

	void keyPressEvent(QKeyEvent* t_event) override {
		if (t_event->key() != Qt::Key_Escape) {
			QDialog::keyPressEvent(t_event);
		}
	}

public:

	ForgeControl();

	void hasTitle(bool t_title);

	void setTitle(QString t_title);

	void setCentralWidget(QWidget* t_widget);

	void setHandle(FWidget* t_handle);
	
	void stateChanged(Qt::ApplicationState state);

	void setPersistent(bool t_persistent);

	void setControlled(ForgeWindow* t_parent);
	
	bool isMoving() {
		return m_handle != nullptr && 
			   m_handle->isDragging();
	}

	bool persistent() { 
		return m_persistent; 
	}

	QVector2D anchor() { 
		return m_anchor; 
	}

	void setAnchor(QVector2D t_anchor) {
		m_anchor = t_anchor;
	}

	WindowSide side() { 
		return m_side; 
	}

};

#endif