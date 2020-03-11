#pragma once

#include "HasIdentifier.h"

#include <map>
#include <vector>

#define gt_zero(s) if(s <= 0) return nullptr

template<class T, class B> struct Derived_from {
	static void constraints(T* p) { B* pb = p; }
	Derived_from() { void(*p)(T*) = constraints; }
};

template<class T> class IdentifierList
	: Derived_from<T, HasIdentifier> {
private:

	std::map<uint, T*> m_objs;

	std::vector<uint> m_ids;

public:
	IdentifierList() : m_objs() {}

	void add(T* t_obj) {
		m_objs[t_obj->id()] = t_obj;
		m_ids.push_back(t_obj->id());
	}

	void remove(T* t_obj) {
		remove(t_obj->id());
	}

	void remove(uint t_id) {
		m_objs.erase(t_id);
		m_ids.erase(std::remove(
			m_ids.begin(), m_ids.end(), t_id),
			m_ids.end());
	}

	T* find(uint t_id) {
		gt_zero(m_objs.count(t_id));
		return m_objs[t_id];
	}

	T* first() {
		gt_zero(m_objs.size());
		return m_objs.begin()->second;
	}

	bool contains(T* t_obj) {
		return m_objs.count(t_obj->id()) != 0;
	}

	void prioritize(uint t_id) {
		// find a reverse iterator pointing to the id 't_id'
		auto it = std::find_if(m_ids.rbegin(), m_ids.rend(), [t_id](auto i) {
			return t_id == i;
			});

		// rotate the found id to the end of the vector
		std::rotate(m_ids.rbegin(), it, m_ids.rend());
	}

	std::vector<T*> priority() {
		// copy the id buffer and reverse it
		// to get a forward-priority list
		std::vector<uint> ids(m_ids.rbegin(), m_ids.rend());
		std::vector<T*> result(ids.size());

		// copy the objects in order into the 
		// output vector
		for (int i = 0; i < ids.size(); ++i) {
			result[i] = find(ids[i]);
		}

		return result;
	}

	T* high() {
		gt_zero(m_ids.size());
		auto id = m_ids.back();

		gt_zero(m_objs.count(id));
		return m_objs[id];
	}

	size_t size() {
		return m_objs.size();
	}

};