#include "EventFilters.h"

#include "Messages.h"
#include "Defines.h"

#define _redirect(M,T)								\
	if (event->type() == M) {						\
		auto handler = dynamic_cast<Handler*>(obj);	\
		auto message = dynamic_cast<T*>(event);		\
		if (handler != nullptr) {					\
			Messages::instance()->publish(			\
				handler,							\
				m_channel,							\
				message);							\
		}											\
	}												\

/*! \brief Event filter to capture the close event and emit it
 *		   as an "onClose" signal.
 */
bool CloseEventFilter::eventFilter(QObject* obj, QEvent* event) {
	_redirect(QEvent::Close, QCloseEvent);
	return QObject::eventFilter(obj, event);
}

/*! \brief Event filter to capture the click event.
 */
bool ClickEventFilter::eventFilter(QObject* obj, QEvent* event) {
	_redirect(QEvent::MouseButtonPress, QMouseEvent);
	return QObject::eventFilter(obj, event);
}