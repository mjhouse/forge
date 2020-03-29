#ifndef __FSYMBOL_H__
#define __FSYMBOL_H__

#include "FGeometry.h"
#include "json.hpp"

#include <QVector3D>

#include <string>
#include <vector>
#include <variant>

using json      = nlohmann::json;
using FProperty = std::variant<int, float, std::string>;

#define _setter(T)													\
	void setProperty(std::string t_name, T t_value) {				\
		if (!hasProperty<T>(t_name,t_value)){						\
			m_properties[t_name] = t_value;							\
			propertyChanged(t_name,m_properties[t_name]);			\
		}															\
	}																\

class FSymbol {
private:

	std::map<std::string, FProperty> m_properties;

protected:
	virtual void propertyChanged(std::string t_name, FProperty t_property) = 0;

public:

	FSymbol()
		: m_properties() {}

	FSymbol(FSymbol* t_other)
		: m_properties(t_other->m_properties) {}

	virtual ~FSymbol() {}

	static FSymbol* from(std::string& t_type);

	virtual FSymbol* copy() = 0;
	
	virtual void setGeometry(std::vector<QVector3D>& t_points) = 0;

	virtual FGeometry* toGeometry() = 0;

	virtual void updateGeometry() = 0;

	/* Check that property exists, has type T and value t_value */
	template <typename T>
	inline bool hasProperty(std::string t_name, T t_value) {
		return (hasProperty<T>(t_name) &&
			std::get<T>(m_properties[t_name]) == t_value);
	}

	/* Check that property exists, and has the given type */
	template <typename T>
	inline bool hasProperty(std::string t_name) {
		return (m_properties.count(t_name) != 0 &&
			std::holds_alternative<T>(m_properties[t_name]));
	}

	_setter(int);
	_setter(float);
	_setter(std::string);

	void setProperty(std::string t_name, json::value_t t_type, json t_value);
	
	template <typename T>
	T property(std::string t_name) {
		return std::get<T>(m_properties[t_name]);
	}

};

#undef _setter
#endif