#include "ForgeApplication.h"
#include "IsControl.h"

#include <iostream>

#define distance(p1,p2) std::sqrtf( std::powf(p2.x() - p1.x(),2) + std::pow(p2.y() - p1.y(),2))

namespace components {

	IsControl::IsControl() 
		: m_parent(nullptr) 
	{
	}

	bool IsControl::isControlled() { 
		return m_parent != nullptr; 
	}

	void IsControl::updateControl(QRect t_rect) {
		m_rect = t_rect;
	}

	void IsControl::positionControl() {
		auto parent = ForgeApplication::instance()->findWindow(m_rect.center());

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

		findSide(m_rect);
	}

	void IsControl::findSide(QRect t_rect) {
		if (m_parent != nullptr) {
			auto pr = m_parent->rect();
			auto pc = pr.center();
			auto cc = QVector2D(t_rect.topLeft());
			
			auto tl = QVector2D(pr.topLeft());
			auto tr = QVector2D(pr.topRight());
			auto br = QVector2D(pr.bottomRight());
			auto bl = QVector2D(pr.bottomLeft());

			auto tld = distance(tl, cc);
			auto trd = distance(tr, cc);
			auto brd = distance(br, cc);
			auto bld = distance(bl, cc);

			auto o = tld;
			m_anchor = cc - tl;
			m_side = WindowSide::TopLeft;
			
			if (trd < o) {
				o = trd;
				m_anchor = cc - tr;
				m_side = WindowSide::TopRight;
			}
			
			if (brd < o) {
				o = brd;
				m_anchor = cc - br;
				m_side = WindowSide::BottomRight;
			}

			if (bld < o) {
				m_anchor = cc - bl;
				m_side = WindowSide::BottomLeft;
			}
		}
		else {
			m_side = WindowSide::None;
			m_anchor = QVector2D(0,0);
		}
	}

}