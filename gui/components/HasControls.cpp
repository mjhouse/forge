#include "HasControls.h"

namespace components {

	HasControls::~HasControls() {
	};
	
	HasControls::HasControls(QWindow* t_parent)
		: m_parent(t_parent) 
		, m_controls() 
	{

	}
	
	void HasControls::adjustControls(QRect t_rect) {
		auto pr = t_rect.right();
		auto pl = t_rect.left();
		auto pb = t_rect.bottom();
		auto pt = t_rect.top();

		for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
			auto c = it->second->geometry();

			auto x = it->second->position().x();
			auto y = it->second->position().y();

			auto cr = c.right();
			auto cl = c.left();
			auto cb = c.bottom();
			auto ct = c.top();

			int dx = 0;
			dx += cr > pr ? x + (pr - cr) : x;
			dx += cl < pl ? x + (pl - cl) : x;
			x = dx / 2;

			int dy = 0;
			dy += cb > pb ? y + (pb - cb) : y;
			dy += ct < pt ? y + (pt - ct) : y;
			y = dy / 2;

			it->second->setPosition(x, y);
		}
	}

	void HasControls::moveControls(QPoint t_old, QPoint t_new) {
		if (m_controls.empty()) return;
		auto ch = t_new - t_old;
		for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
			it->second->move(it->second->position() + ch);
		}
	}

	IsControl* HasControls::findControl(uint t_id) {
		if (m_controls.count(t_id) > 0) {
			return m_controls[t_id];
		}
		else {
			return nullptr;
		}
	}

	void HasControls::addControl(IsControl* t_control) {
		m_controls[t_control->id()] = t_control;
	}

	void HasControls::removeControl(IsControl* t_control) {
		m_controls.erase(t_control->id());
	}

}