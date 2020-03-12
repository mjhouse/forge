#include "HasIdentifier.h"

/*! \brief Declare the initial counter value */
uint HasIdentifier::count = 0;

/*! \brief Implement the virtual destructor */
HasIdentifier::~HasIdentifier() {}

/*! \brief Default constructor inits the id and 
 *		   increments the global count.
 */
HasIdentifier::HasIdentifier()
	: m_id(count++) {}

/*! \brief Get the id
 */
uint HasIdentifier::id() {
	return m_id;
}

/*! \brief Compare the id of this object to another
 *		   HasIdentifier object. if the other object is
 *		   null, the return value is false.
 */
bool HasIdentifier::is(HasIdentifier* t_object) {
	if (t_object != nullptr) {
		return m_id == t_object->m_id;
	}
	else {
		return false;
	}
}
