#include "Message.h"
#include "Messages.h"
#include "ForgeControl.h"

#include <string>

#include <QMouseEvent>
#include <QFocusEvent>
#include <QCloseEvent>

#define impl_message(V,T)								\
	template<>											\
	Message<V>::Message(Handler* t_sender,				\
						V t_value)						\
		: UnknownMessage(T)								\
		, m_sender(t_sender)							\
		, m_value(t_value)								\
		, m_name(#T)									\
	{}													\
														\
	template<>											\
	V Message<V>::value() {								\
		return m_value;									\
	}													\
														\
	template<>											\
	const char* Message<V>::name() {					\
		return m_name;									\
	}													\
														\
	template<>											\
	Handler* Message<V>::sender() {						\
		return m_sender;								\
	}													\


impl_message(double, MessageType::Double)
impl_message(float, MessageType::Float)
impl_message(int, MessageType::Int)
impl_message(std::string, MessageType::String)

impl_message(QMouseEvent*, MessageType::Event)
impl_message(QFocusEvent*, MessageType::Event)
impl_message(QCloseEvent*, MessageType::Event)

impl_message(Qt::ApplicationState, MessageType::State)
impl_message(Qt::WindowState, MessageType::State)

impl_message(ForgeControl*, MessageType::Control);