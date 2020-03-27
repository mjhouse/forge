#ifndef __BULKLOADER_H__
#define __BULKLOADER_H__

#include "json.hpp"

#include <map>

#include <QString>
#include <QVector2D>

using json = nlohmann::json;

class FSymbol;

class BulkLoader {
private:

	std::map<std::string,std::unique_ptr<FSymbol>> m_symbols;
	
	void loadOne(std::string& t_type, json& t_json);

	void loadMany(json& t_json);

public:
	BulkLoader();

	void load(std::string t_path);

	std::map<std::string, std::unique_ptr<FSymbol>>& symbols();

	FSymbol* get(std::string t_name);

	size_t size();

};

#endif // __BULKLOADER_H__