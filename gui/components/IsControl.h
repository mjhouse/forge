#ifndef __ISCONTROL_H__
#define __ISCONTROL_H__

#include <QDialog>

#include "HasIdentifier.h"
#include "HasControls.h"

namespace components {

	class HasControls;

	class IsControl : public HasIdentifier {
	private:

		QDialog* m_control;

		HasControls* m_parent;

	public:
		IsControl(QDialog* t_control);

		bool controlled();

		void findController();

		QRect geometry() { return m_control->geometry(); }

		void setPosition(float x, float y) {
			m_control->setGeometry(x, y,
				m_control->width(),
				m_control->height());
		}

		QPoint position() { return m_control->pos(); }

		void move(QPoint t_pos) { m_control->move(t_pos); }

	};

}

#endif