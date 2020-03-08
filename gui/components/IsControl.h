#ifndef __ISCONTROL_H__
#define __ISCONTROL_H__

#include <QDialog>
#include <QVector2D>

#include "HasIdentifier.h"
#include "HasControls.h"

namespace components {

	class HasControls;

	enum class WindowSide {
		None,
		TopRight,
		BottomRight,
		BottomLeft,
		TopLeft
	};
	
	class IsControl : public HasIdentifier {
	private:

		WindowSide m_side;

		float m_offset;

		QRect m_rect;

		QVector2D m_anchor;
		
		HasControls* m_parent;

	public:
		IsControl();

		bool isControlled();

		void updateControl(QRect t_rect);

		void positionControl();

		void findSide(QRect t_rect);

		QRect getRect() { return m_rect; }

		WindowSide getSide() { return m_side; }

		float getOffset() { return m_offset; }

		QVector2D getAnchor() { return m_anchor; }

		virtual void setPosition(QPoint t_point) = 0;

	};

}

#endif