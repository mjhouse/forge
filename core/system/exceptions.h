#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>

#define check_null(a,m) if (a == nullptr) throw invalid_argument(m)

class forge_exception : public std::exception {
private:
	const char* m_message;

public:
	forge_exception(const char* t_message) {
		m_message = t_message;
	}

	const char* what() const throw() {
		return "An invalid argument was given";
	}

	const char* message() {
		return m_message;
	} 
};

class invalid_argument : public forge_exception {
public:
	invalid_argument(const char* t_message) : forge_exception(t_message) {}
};

#endif