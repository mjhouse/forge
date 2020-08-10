#include "EventFilters.h"

#include "Messages.h"
#include "Defines.h"
#include "ForgeWindow.h"

/*! \brief Event filter to capture the close event and emit it
 *		   as an "onClose" signal.
 */
bool CloseEventFilter::eventFilter(QObject* t_object, QEvent* t_event) {
	auto window = dynamic_cast<ForgeWindow*>(t_object);
	if (window != nullptr && t_event->type() == QEvent::MouseButtonPress)
		window->onClose((QCloseEvent*)t_event);
	return QObject::eventFilter(t_object, t_event);
}

/*! \brief Event filter to capture the click event.
 */
bool ClickEventFilter::eventFilter(QObject* t_object, QEvent* t_event) {
	auto window = dynamic_cast<ForgeWindow*>(t_object);
	if (window != nullptr && t_event->type() == QEvent::MouseButtonPress) 
		window->onClick((QMouseEvent*)t_event);
	return QObject::eventFilter(t_object, t_event);
}