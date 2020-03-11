#include "ForgeApplication.h"
#include "IsControl.h"

#include <iostream>

//namespace  {

	//IsControl::IsControl() 
	//	: m_side(WindowSide::None)
	//	, m_anchor(0,0)
	//	, m_parent(nullptr) 
	//	, m_persistent(false)
	//{
	//}

	//void IsControl::positionWithin(HasControls* t_parent) {
	//	auto p = t_parent->rect();
	//	auto c = geometry();

	//	int t = p.top();
	//	int r = p.right();
	//	int b = p.bottom();
	//	int l = p.left();

	//	int cx = c.x();
	//	int cy = c.y();

	//	cx = std::min(std::max(cx, l), r - c.width());
	//	cy = std::min(std::max(cy, t), b - c.height());

	//	setGeometry(cx,cy,width(),height());
	//}

	//void IsControl::moveEvent(QMoveEvent* t_event) {
	//	if (!isControlled() || isMoving()) {
	//		auto rect = geometry();
	//		auto parent = ForgeApplication::instance()->findWindow(rect.center());

	//		if (parent) {
	//			if (m_parent)
	//				m_parent->removeControl(this);

	//			parent->addControl(this);
	//			m_parent = parent;
	//		}
	//		else {
	//			if (m_parent)
	//				m_parent->removeControl(this);
	//			m_parent = nullptr;
	//		}

	//		findSide(rect);
	//	}
	//}

	//void IsControl::findSide(QRect t_rect) {
	//	if (m_parent != nullptr) {
	//		auto pr = m_parent->rect();
	//		auto pc = pr.center();
	//		auto cc = QVector2D(t_rect.topLeft());
	//		
	//		auto tl = QVector2D(pr.topLeft());
	//		auto tr = QVector2D(pr.topRight());
	//		auto br = QVector2D(pr.bottomRight());
	//		auto bl = QVector2D(pr.bottomLeft());

	//		auto tld = distance(tl, cc);
	//		auto trd = distance(tr, cc);
	//		auto brd = distance(br, cc);
	//		auto bld = distance(bl, cc);

	//		auto o = tld;
	//		m_anchor = cc - tl;
	//		m_side = WindowSide::TopLeft;
	//		
	//		if (trd < o) {
	//			o = trd;
	//			m_anchor = cc - tr;
	//			m_side = WindowSide::TopRight;
	//		}
	//		
	//		if (brd < o) {
	//			o = brd;
	//			m_anchor = cc - br;
	//			m_side = WindowSide::BottomRight;
	//		}

	//		if (bld < o) {
	//			m_anchor = cc - bl;
	//			m_side = WindowSide::BottomLeft;
	//		}
	//	}
	//	else {
	//		m_side = WindowSide::None;
	//		m_anchor = QVector2D(0,0);
	//	}
	//}

	//bool IsControl::isControlled() {
	//	return m_parent != nullptr;
	//}

	//void IsControl::setControlled(HasControls* t_parent) {
	//	if (m_parent)
	//		m_parent->removeControl(this);

	//	m_parent = t_parent;
	//	m_parent->addControl(this);

	//	positionWithin(m_parent);
	//	findSide(geometry());
	//}

	//void IsControl::setPersistent(bool t_persistent) {
	//	m_persistent = t_persistent;
	//}

//}