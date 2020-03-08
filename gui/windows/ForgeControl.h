#ifndef __FORGECONTROL_H__
#define __FORGECONTROL_H__

#include <QtWidgets/QDialog>

#include "ForgeTitleBar.h"
#include "IsControl.h"

using namespace components;

class ForgeControl : public QDialog, 
					 public IsControl {
private:

	//ForgeWindow* m_parent;

	ForgeTitleBar* m_title;

	QWidget* m_body;

	FWidget* m_handle;

	bool m_hasTitle;

	void moveEvent(QMoveEvent* t_event) override;

public:

	ForgeControl();

	void hasTitle(bool t_title);

	void setTitle(QString t_title);

	void setCentralWidget(QWidget* t_widget);

	void setHandle(FWidget* t_handle);
	
	void stateChanged(Qt::ApplicationState state);

	void setPosition(QPoint t_point) {
		setGeometry(t_point.x(), t_point.y(),
			width(), height());
		updateControl(geometry());
	}
};

#endif