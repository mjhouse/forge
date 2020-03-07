#ifndef __HASCONTROLS_H__
#define __HASCONTROLS_H__

#include <QWindow>
#include <QWidget>
#include <QEvent>

#include "IsControl.h"

#include <vector>
#include <map>

namespace components {

	class IsControl;

	class HasControls{
	private:

		QRect m_old;

		QWindow* m_parent;

		std::map<uint, IsControl*> m_controls;
		
		int findClosest(QRect& t_rect, QPoint t_point);

	public:
		HasControls(QWindow* t_parent);

		// HasControls cannot be instantiated
		virtual ~HasControls() = 0;

		void adjustControls(QRect t_rect);
		
		void moveControls(QPoint t_old, QPoint t_new);

		IsControl* findControl(uint t_id);

		void addControl(IsControl* t_control);

		void removeControl(IsControl* t_control);

	};

}

#endif