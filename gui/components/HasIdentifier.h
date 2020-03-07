#pragma once

typedef unsigned int uint;

namespace components {

	class HasIdentifier {
	private:
		static uint count;

		uint m_id;

	public:
		HasIdentifier();

		// HasIdentifier cannot be instantiated
		virtual ~HasIdentifier() = 0;

		uint id();

		bool is(HasIdentifier* t_object);
	};

}

