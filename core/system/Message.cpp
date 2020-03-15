#include "Message.h"
#include "Messages.h"

#include <string>

#include <QMouseEvent>

#define impl_message(V,T)								\
	Message<V>::Message(Handler* t_sender,	\
						V t_value)						\
		: UnknownMessage(T)								\
		, m_sender(t_sender)							\
		, m_value(t_value)								\
		, m_name(#T)									\
	{}													\
														\
	V Message<V>::value() {								\
		return m_value;									\
	}													\
														\
	const char* Message<V>::name() {					\
		return m_name;									\
	}													\
														\
	Handler* Message<V>::sender() {						\
		return m_sender;								\
	}													\


impl_message(double, MessageType::Double)
impl_message(float, MessageType::Float)
impl_message(int, MessageType::Int)
impl_message(std::string, MessageType::String)
impl_message(QMouseEvent*, MessageType::MouseEvent)