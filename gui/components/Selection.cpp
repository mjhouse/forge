#include "Selection.hpp"

Selection* Selection::get() {
	static Selection selection;
	return &selection;
}

std::vector<FModel*> Selection::selection() {
	return m_selected;
}

bool Selection::contains(FModel* t_model) {
	return std::find(
		m_selected.begin(), m_selected.end(), t_model) != m_selected.end();
}

void Selection::add(FModel* t_model) {
	if (t_model == nullptr || contains(t_model)) 
		return;
	
	t_model->highlight();
	m_selected.push_back(t_model);
	
	emit onSelected(t_model);
	emit selectionChanged();
}

void Selection::remove(FModel* t_model) {
	if (t_model == nullptr) return;
	t_model->unHighlight();

	m_selected.erase(std::remove(
		m_selected.begin(), m_selected.end(), t_model));

	emit onUnselected(t_model);
	emit selectionChanged();
}

void Selection::clear() {
	for (auto model : m_selected)
		model->unHighlight();
	m_selected.clear();
}