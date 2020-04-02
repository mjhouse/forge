#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "Logger.h"
#include <exception>

#define _throw(t,m) throw t(__FILE__,__LINE__,m)
#define check_null(a,m) if (a == nullptr) _throw(invalid_argument,m)

#define _impl_exception(N)					\
	class N : public forge_exception {		\
		public:								\
			N(const char* t_file,			\
			  const int   t_line,			\
			  const char* t_message)		\
			: forge_exception(				\
				t_file,						\
				t_line,						\
				t_message)					\
			{}								\
	};										\

using LogLevel = logging::LogLevel;

class forge_exception : public std::exception {
private:

	const char* m_file;

	const int m_line;

	const char* m_message;

public:
	forge_exception(const char* t_file,
				    const int   t_line,
				    const char* t_message)
		: m_file(t_file)
		, m_line(t_line)
		, m_message(t_message)
	{}

	const char* file() const throw()
		{ return m_file; }

	const int line() const throw()
		{ return m_line; }

	const char* message() const throw() 
		{ return m_message; }

	const char* what() const throw() 
		{ return message(); }

	void log(const LogLevel t_level) {
		logging::Logger::instance()->log(
			m_file, 
			m_line, 
			t_level,
			m_message);
	}

};

_impl_exception(invalid_argument);
_impl_exception(cannot_open_file);

#undef _impl_exception
#endif