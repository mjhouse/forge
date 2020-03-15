#include "Messages.h"

#include <QMouseEvent>

#define route(T,C,E) case QEvent::Type::T:							\
	Messages::instance()->publish(handler, C, (E)t_event); break;	\


bool MessageEventFilter::eventFilter(QObject* t_object, QEvent* t_event) {
	auto handler = dynamic_cast<Handler*>(t_object);
	if (handler != nullptr) {
		switch (t_event->type()) {
			route(MouseButtonPress, Channel::Action, QMouseEvent*);
			route(MouseButtonRelease, Channel::Action, QMouseEvent*);
			route(MouseMove, Channel::Action, QMouseEvent*);
		}
	}

	return QObject::eventFilter(t_object, t_event);
}

void Messages::subscribe(Handler* t_subscriber, Channel t_channel) {
	std::lock_guard<std::mutex> guard(m_lock);
	m_subscribers[t_channel].insert(t_subscriber);
}

void Messages::unsubscribe(Handler* t_subscriber, Channel t_channel) {
	std::lock_guard<std::mutex> guard(m_lock);
	m_subscribers[t_channel].erase(t_subscriber);
}