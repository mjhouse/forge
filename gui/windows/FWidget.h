#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets>

class FWidget : public QWidget {
private:

	bool moving;

	QWidget* target;

	bool drag;

	int oX = 0;

	int oY = 0;

	void mousePressEvent(QMouseEvent* t_event) override {
		if (drag && target != nullptr) {
			auto r = this->rect().topLeft();
			oX = t_event->x() - r.x();
			oY = t_event->y() + r.y();
			moving = true;
		}
	}

	void mouseReleaseEvent(QMouseEvent* t_event) override {
		if (drag && target != nullptr) {
			oX = 0;
			oY = 0;
			moving = false;
		}
	}

	void mouseMoveEvent(QMouseEvent* t_event) override {
		if (drag && moving && target != nullptr) {
			target->move(t_event->globalPos().x() - oX,
						 t_event->globalPos().y() - oY);
		}
	}

public:
	FWidget() 
		: moving(false)
		, target(nullptr)
		, drag(false)
	{}

	FWidget(QWidget* t_parent) 
		: QWidget(t_parent)
		, moving(false)
		, target(nullptr)
		, drag(false)
	{}

	void setDragTarget(QWidget* t_target) {
		target = t_target;
	}

	void setDrag(bool t_drag) {
		this->drag = t_drag;
	}

	bool isDragging() {
		return moving;
	}

};