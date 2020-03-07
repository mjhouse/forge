#include "ForgeApplication.h"
#include "IsControl.h"

namespace components {

	IsControl::IsControl(QDialog* t_control) 
		: m_control(t_control)
		, m_parent(nullptr) 
	{
	}

	bool IsControl::controlled() { 
		return m_parent != nullptr; 
	}

	void IsControl::findController() {
		auto center = m_control->geometry().center();
		auto parent = ForgeApplication::instance()->findWindow(center);

		if (parent) {
			if (m_parent)
				m_parent->removeControl(this);

			parent->addControl(this);
			m_parent = parent;
		}
		else {
			if (m_parent)
				m_parent->removeControl(this);
			m_parent = nullptr;
		}
	}

}