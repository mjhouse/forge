#include "Messages.h"

#include <QMouseEvent>

size_t Handler::g_count = 0;

void Messages::subscribe(Handler* t_subscriber, Channel t_channel) {
	std::lock_guard<std::mutex> guard(m_lock);
	m_subscribers[t_channel].insert(t_subscriber);
}

void Messages::unsubscribe(Handler* t_subscriber, Channel t_channel) {
	std::lock_guard<std::mutex> guard(m_lock);
	m_subscribers[t_channel].erase(t_subscriber);
}