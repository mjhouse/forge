#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include "json.hpp"

#include <QVector3D>

#include <string>
#include <vector>
#include <variant>

#define _match(f,t,N,T,V) if(T == json::value_t::f) return setProperty(N,(t)V)
#define _setter(T)													\
	void setProperty(std::string t_name, T t_value) {				\
		m_properties[t_name] = t_value;								\
	}																\

using json = nlohmann::json;

class FSymbol {
private:

	std::map<std::string, std::variant<int,float,std::string>> m_properties;

public:
	static FSymbol* from(std::string& t_type);

	virtual void setGeometry(std::vector<QVector3D>& t_points) = 0;
	
	template <typename T>
	T property(std::string t_name) {
		return std::get<T>(m_properties[t_name]);
	}

	_setter(int)
	_setter(float)
	_setter(std::string)

	void setProperty(std::string t_name, json::value_t t_type, json t_value) {
		_match(number_integer, int, t_name, t_type, t_value);
		_match(number_float, float, t_name, t_type, t_value);
		_match(string, std::string, t_name, t_type, t_value);
	}
	
};

#endif