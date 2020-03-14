#ifndef __FORGECONTROL_H__
#define __FORGECONTROL_H__

#include <QtWidgets/QDialog>

#include "HasIdentifier.h"
#include "ForgeTitleBar.h"

class ForgeWindow;

class ForgeControl : public QDialog, 
					 public HasIdentifier {
private:

	ForgeTitleBar* m_title;		/*!< The dialog title */

	QWidget* m_body;			/*!< The central widget body */

	FWidget* m_handle;			/*!< A widget used as a handle for dragging */

	bool m_hasTitle;			/*!< Has a default title bar if true */
		
	QVector2D m_anchor;			/*!< A reference point relative to the parent */
	
	ForgeWindow* m_parent;		/*!< The current parent window */
	
	bool m_persistent;			/*!< Passed to another window when parent closes if true */

	bool m_minimized;			/*!< If true, control is hidden because parent is minimzed */

	bool m_unexposed;

	QPoint positionWithin(QRect& t_parent, QRect& t_child);

	void findAnchor(QRect& t_rect);

	void moveEvent(QMoveEvent* t_event) override;

	void keyPressEvent(QKeyEvent* t_event) override;
	
	void disconnectParent();

	void connectParent();

	void parentStateChanged(Qt::WindowState t_state);

protected:

	virtual void onParentMouseMove(QPoint t_point);

	virtual void onParentMouseClick(QPoint t_point);

public:

	ForgeControl();

	void onClick(QMouseEvent* t_event);

	void hasTitle(bool t_title);

	void setTitle(QString t_title);

	void setCentralWidget(QWidget* t_widget);

	void setHandle(FWidget* t_handle);
	
	void stateChanged(Qt::ApplicationState state);

	void setControlled(ForgeWindow* t_parent);
	
	bool isMoving();

	bool persistent();

	void setPersistent(bool t_persistent);

	QVector2D anchor();

	void setAnchor(QVector2D t_anchor);

};

#endif // __FORGECONTROL_H__