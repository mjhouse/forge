#ifndef __SELECTION_HPP__
#define __SELECTION_HPP__

#include "FModel.h"
#include <QOBject>

class Selection : public QObject {
	Q_OBJECT

private:

	std::vector<FModel*> m_selected;

	Selection() : m_selected() {}

public:
	static Selection* get();

	std::vector<FModel*> selection();

	bool contains(FModel* t_model);

	void add(FModel* t_model);

	void remove(FModel* t_model);

	void clear();

signals:

	void onSelected(FModel* t_model);

	void onUnselected(FModel* t_model);

	void selectionChanged();

};

#endif