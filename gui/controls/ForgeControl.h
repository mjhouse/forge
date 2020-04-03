#ifndef __FORGECONTROL_H__
#define __FORGECONTROL_H__

#include <QtWidgets/QDialog>

#include "HasIdentifier.h"
#include "ForgeTitleBar.h"
#include "Messages.h"
#include "Message.h"

class ForgeWindow;

class ForgeControl : public QDialog, 
					 public HasIdentifier,
					 public Handler {
private:

	ForgeTitleBar* m_title;		/*!< The dialog title */

	QWidget* m_body;			/*!< The central widget body */

	FWidget* m_handle;			/*!< A widget used as a handle for dragging */

	bool m_hasTitle;			/*!< Has a default title bar if true */
		
	QVector2D m_anchor;			/*!< A reference point relative to the parent */
	
	QVector2D m_initial;		/*!< The default position relative to the parent window */

	ForgeWindow* m_parent;		/*!< The current parent window */
	
	bool m_initialized;			/*!< Flag set when control has been displayed at least once */

	bool m_persistent;			/*!< Passed to another window when parent closes if true */

	bool m_minimized;			/*!< If true, control is hidden because parent is minimzed */

	// utility functions
	QPoint positionWithin(const QRect& t_parent, const QRect& t_child);

	void findAnchor(QRect& t_rect);

	// internal event handlers
	void moveEvent(QMoveEvent* t_event) override;

	void keyPressEvent(QKeyEvent* t_event) override;
	
	// message handlers
	void appStateChanged(Message<Qt::ApplicationState>* state);

	void winStateChanged(Message<Qt::WindowState>* t_state);

	void showEvent(QShowEvent* t_event) override;

public:

	ForgeControl(ForgeWindow* t_parent, float t_x, float t_y);
	
	// properties
	void hasTitle(bool t_title);

	void setTitle(QString t_title);

	void setCentralWidget(QWidget* t_widget);

	void setHandle(FWidget* t_handle);
	
	void setControlled(ForgeWindow* t_parent);
	
	ForgeWindow* controller();

	bool isMoving();

	bool persistent();
	
	void setPersistent(bool t_persistent);

	QVector2D anchor();

	void setAnchor(QVector2D t_anchor);

	virtual void onMessage(Channel t_channel, UnknownMessage& t_message);

};

#endif // __FORGECONTROL_H__