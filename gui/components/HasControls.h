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

		QRect m_rect;

		QPoint m_point;

		std::map<uint, IsControl*> m_controls;

	public:
		HasControls();

		// HasControls cannot be instantiated
		virtual ~HasControls() = 0;

		void updateRect(QRect t_rect);

		void updatePosition(QPoint t_point);

		void updateControls();

		IsControl* findControl(uint t_id);

		void addControl(IsControl* t_control);

		void removeControl(IsControl* t_control);

		QRect rect();

		QPoint point();

	};

}

#endif