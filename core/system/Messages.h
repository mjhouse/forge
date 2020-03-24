#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "Message.h"

#include <set>
#include <string>
#include <map>
#include <mutex>

#include <QObject>
#include <QEvent>

#define _publish(c,m) Messages::instance()->publish(this, c, m);
#define _subscribe(c) Messages::instance()->subscribe(this, c);

// redirect an unknown message to the
// appropriate handler
#define _route_in(c,v,C,V,H)			\
	if (c == C) {						\
		if (auto message = v.to<V>()) {	\
			H(message);					\
		}								\
	}									\

// route a signal to a channel
#define _event_publish(E,C)				\
	(void)this->connect(this, &E,		\
						this,			\
		[=](auto m) {					\
			_publish(C, m);				\
	})									\

// route an event handler to a channel
#define _method_publish(N,E,C)			\
	void N(E* e) override {				\
		_publish(C, e);					\
	}									\

enum class Channel {
	Debug,
	Action,
	Reassign
};

class Handler {
private:
	static size_t g_count;

	size_t m_id;

public:
	Handler() : m_id(++g_count) {}

	bool isHandler(Handler* t_other) { return m_id == t_other->m_id; }

	virtual void onMessage(Channel t_channel, UnknownMessage& t_message) = 0;
};

class Messages {
private:

	std::recursive_mutex m_lock;

	std::map<Channel, std::set<Handler*>> m_subscribers;

	Messages(){}

public:

	static Messages* instance() {
		static Messages messages;
		return &messages;
	}

	void subscribe(Handler* t_subscriber, Channel t_channel);

	void unsubscribe(Handler* t_subscriber, Channel t_channel);

	template <typename T>
	void publish(Handler* t_sender, Channel t_channel, T t_message) {
		m_lock.lock();
		if (m_subscribers.count(t_channel) == 1) {
			Message<T> message(t_sender, t_message);
			for (auto subscriber : m_subscribers[t_channel]) {
				subscriber->onMessage(t_channel, message);
			}
		}
		m_lock.unlock();
	}

};

#endif