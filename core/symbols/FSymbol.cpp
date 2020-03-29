#include "FSymbol.h"
#include "FCrossSection.h"
#include "FLine.h"

#define _match(f,t,N,T,V)											\
	if(T == json::value_t::f) return setProperty(N,(t)V)			\

FSymbol* FSymbol::from(std::string& t_type) {
	if (t_type == "CrossSection") return (FSymbol*)new FCrossSection();
	if (t_type == "Line")		  return (FSymbol*)new FLine();
	return nullptr;
}

void FSymbol::setProperty(std::string t_name, json::value_t t_type, json t_value) {
	_match(number_integer, int, t_name, t_type, t_value);
	_match(number_float, float, t_name, t_type, t_value);
	_match(string, std::string, t_name, t_type, t_value);
}

#undef _match