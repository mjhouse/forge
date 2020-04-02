#ifndef __EVENTFILTERS_H__
#define __EVENTFILTERS_H__
#pragma warning (disable : 4068 )

#include <QObject>

#include "Messages.h"

/*! \brief Event filter for close events
 */
class CloseEventFilter : public QObject {
	Q_OBJECT

private:

	Channel m_channel;

public:
	CloseEventFilter(QObject* parent, Channel t_channel) 
		: QObject(parent), m_channel(t_channel) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

/*! \brief Event filter for click events
 */
class ClickEventFilter : public QObject {
	Q_OBJECT

private:

	Channel m_channel;

public:
	ClickEventFilter(QObject* parent, Channel t_channel)
		: QObject(parent), m_channel(t_channel) {}

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

#endif // __EVENTFILTERS_H__