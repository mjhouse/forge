#ifndef __SELECTION_HPP__
#define __SELECTION_HPP__

#include "FModel.h"
#include <QOBject>

class Selection : public QObject {
	Q_OBJECT

private:

	std::vector<FModel*> m_selected;

	bool m_lock;

	Selection() 
		: m_selected() 
		, m_lock(false) 
	{}

public:
	static Selection* get();

	std::vector<FModel*> selection();

	bool contains(FModel* t_model);

	void add(FModel* t_model);

	void remove(FModel* t_model);

	void clear();

	void lock()
	{ m_lock = true; }

	void unlock()
	{ m_lock = false; }

	bool isEmpty()
	{ return m_selected.size() == 0; }

signals:

	void onSelected(FModel* t_model);

	void onUnselected(FModel* t_model);

	void selectionChanged();

};

#endif