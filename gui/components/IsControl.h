#ifndef __ISCONTROL_H__
#define __ISCONTROL_H__

#include <QDialog>
#include <QVector2D>

#include "HasIdentifier.h"
#include "HasControls.h"

//namespace components {

	//class HasControls;

	//enum class WindowSide {
	//	None,
	//	TopRight,
	//	BottomRight,
	//	BottomLeft,
	//	TopLeft
	//};
	//
	//class IsControl : public QDialog, public HasIdentifier {
	//private:

	//	WindowSide m_side;

	//	QVector2D m_anchor;
	//	
	//	HasControls* m_parent;

	//	bool m_persistent;

	//	void positionWithin(HasControls* t_parent);

	//	void moveEvent(QMoveEvent* t_event) override;

	//	void findSide(QRect t_rect);

	//public:
	//	IsControl();

	//	//bool isControlled();

	//	void setControlled(HasControls* t_parent);

	//	HasControls* controller() { return m_parent; }

	//	QVector2D anchor() { return m_anchor; }

	//	WindowSide side() { return m_side; }

	//	bool persistent() { return m_persistent; }

	//	void setPersistent(bool t_persistent);

	//	void reassign() { moveEvent(nullptr); }

	//	virtual bool isMoving() = 0;

	//};

//}

#endif