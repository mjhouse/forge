#ifndef __MESSAGE_H__
#define __MESSAGE_H__

enum class MessageType {
	Empty,
	Double,
	Float,
	Int,
	String,
	Event,
	State,
	Control
};

template <typename T>
class Message;
class Handler;

class UnknownMessage {
private:

	const MessageType m_type;

public:
	UnknownMessage(MessageType t_type)
		: m_type(t_type) {}

	virtual ~UnknownMessage() = default;

	template <typename T>
	Message<T>* to() {
		return dynamic_cast<Message<T>*>(this);
	}

	MessageType type() const { 
		return m_type; 
	}

};

template <typename T>
class Message : public UnknownMessage {
private:

	Handler* m_sender;

	T m_value;

	const char* m_name;
	
public:
	Message(Handler* t_sender, T t_value);

	T value();
	
	const char* name();

	Handler* sender();

};

#endif