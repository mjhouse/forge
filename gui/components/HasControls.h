#ifndef __HASCONTROLS_H__
#define __HASCONTROLS_H__

#include <QWindow>
#include <QWidget>
#include <QEvent>

#include <vector>
#include <map>

class ForgeControl;

class HasControls {
private:

	QRect m_rect;

	QPoint m_point;

	std::map<uint, ForgeControl*> m_controls;

public:
	HasControls();

	// HasControls cannot be instantiated
	virtual ~HasControls() = 0;

	void updateControls(QRect& oldRect, QRect& newRect);

	ForgeControl* findControl(uint t_id);

	void addControl(ForgeControl* t_control);

	void removeControl(ForgeControl* t_control);

	std::vector<ForgeControl*> allControls();

};

#endif