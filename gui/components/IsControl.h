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

		QDialog* getControl() { return m_control; }
	};

}

#endif