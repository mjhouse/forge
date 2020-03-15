#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "Message.h"

#include <set>
#include <string>
#include <map>
#include <mutex>

#include <QObject>
#include <QEvent>

#define publish_debug(m)  Messages::instance()->publish(this, Channel::Debug, m);
#define publish_action(m) Messages::instance()->publish(this, Channel::Action, m);

enum class Channel {
	Debug,
	Action
};

class Handler {
public:
	virtual void onMessage(Channel t_channel, UnknownMessage& t_message) = 0;
};

class MessageEventFilter : public QObject {
	Q_OBJECT
public:
	MessageEventFilter(QObject* parent) : QObject(parent) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

class Messages {
private:

	std::mutex m_lock;

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
		std::lock_guard<std::mutex> guard(m_lock);
		if (m_subscribers.count(t_channel) == 1) {
			Message<T> message(t_sender, t_message);
			for (auto subscriber : m_subscribers[t_channel]) {
				subscriber->onMessage(t_channel, message);
			}
		}
	}

};

#endif