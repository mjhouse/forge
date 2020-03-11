#include "HasControls.h"
#include "ForgeControl.h"

#include <QDebug>
#include <QVector2D>

namespace components {

	HasControls::~HasControls() {
	};
	
	HasControls::HasControls()
		: m_controls() 
	{}

	void HasControls::updateControls(QRect& oldRect, QRect& newRect) {
		m_rect = newRect;

		auto cx = (float)newRect.width()  / oldRect.width();
		auto cy = (float)newRect.height() / oldRect.height();

		for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
			auto control = it->second;
			auto cr = control->geometry();
			auto a = control->anchor();

			// scale the anchor values to the new size
			a.setX(a.x() * cx);
			a.setY(a.y() * cy);

			float x = a.x() + m_rect.x() - (cr.width()  / 2);
			float y = a.y() + m_rect.y() - (cr.height() / 2);
			
			float l = m_rect.x();
			float t = m_rect.y();
			float r = l + m_rect.width();
			float b = t + m_rect.height();

			x = std::min(std::max(x, l), r - cr.width());
			y = std::min(std::max(y, t), b - cr.height());

			control->setAnchor(a);
			control->move(x,y);
		}
	}

	ForgeControl* HasControls::findControl(uint t_id) {
		if (m_controls.count(t_id) > 0) {
			return m_controls[t_id];
		}
		else {
			return nullptr;
		}
	}

	void HasControls::addControl(ForgeControl* t_control) {
		m_controls[t_control->id()] = t_control;
	}

	void HasControls::removeControl(ForgeControl* t_control) {
		m_controls.erase(t_control->id());
	}

	std::vector<ForgeControl*> HasControls::allControls() {
		std::vector<ForgeControl*> controls;

		for (auto control : m_controls)
			controls.push_back(control.second);

		return controls;
	}



}