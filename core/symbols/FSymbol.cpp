#include "FSymbol.h"
#include "FCrossSection.h"
#include "FLine.h"

FSymbol* FSymbol::from(std::string& t_type) {
	if (t_type == "CrossSection") return (FSymbol*)new FCrossSection();
	if (t_type == "Line")		  return (FSymbol*)new FLine();
	return nullptr;
}