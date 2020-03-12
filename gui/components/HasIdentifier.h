#ifndef __HASIDENTIFIER_H__
#define __HASIDENTIFIER_H__

typedef unsigned int uint;

class HasIdentifier {
private:
	static uint count;	/*!< The global id counter */

	uint m_id;			/*!< The id of this object */

public:
	HasIdentifier();

	/*! \brief HasIdentifier cannot be instantiated, although
	 *		   no methods need to be implemented to use the class.
	*/
	virtual ~HasIdentifier() = 0;

	uint id();

	bool is(HasIdentifier* t_object);
};

#endif // __HASIDENTIFIER_H__