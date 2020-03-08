#include "HasControls.h"

#include <QDebug>
#include <QVector2D>

namespace components {

	HasControls::~HasControls() {
	};
	
	HasControls::HasControls()
		: m_controls() 
	{}

	void HasControls::updateRect(QRect t_rect) {
		m_rect = t_rect;
	}

	void HasControls::updatePosition(QPoint t_point) {
		m_point = t_point;
	}

	void HasControls::updateControls() {

		for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
			auto control = it->second;
			QVector2D anchor = control->getAnchor();

			auto tl = QVector2D(m_rect.topLeft());
			auto tr = QVector2D(m_rect.topRight());
			auto br = QVector2D(m_rect.bottomRight());
			auto bl = QVector2D(m_rect.bottomLeft());

			switch (control->getSide()) {
				case WindowSide::TopLeft:
					anchor += tl;
					break;
				case WindowSide::TopRight:
					anchor += tr;
					break;
				case WindowSide::BottomRight:
					anchor += br;
					break;
				case WindowSide::BottomLeft:
					anchor += bl;
					break;
			}
			control->setPosition(QPoint(anchor.x(),anchor.y()));
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

	QRect HasControls::rect() {
		return m_rect;
	}

	QPoint HasControls::point() {
		return m_point;
	}

}