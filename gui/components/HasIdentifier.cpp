#include "HasIdentifier.h"

uint HasIdentifier::count = 0;

HasIdentifier::~HasIdentifier() {}

HasIdentifier::HasIdentifier()
	: m_id(count++) {}

uint HasIdentifier::id() {
	return m_id;
}

bool HasIdentifier::is(HasIdentifier* t_object) {
	if (t_object != nullptr) {
		return m_id == t_object->m_id;
	}
	else {
		return false;
	}
}
