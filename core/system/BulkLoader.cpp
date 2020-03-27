#include "BulkLoader.h"
#include "FModel.h"
#include "FCrossSection.h"
#include "FModelExtruded.h"
#include "FModelLine.h"
#include "FLine.h"

#include <QVector3D>

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

void BulkLoader::loadOne(std::string& t_type, json& t_json) {
	FSymbol* symbol = FSymbol::from(t_type);
	std::vector<QVector3D> points;

	auto geometry   = t_json["geometry"];
	auto properties = t_json["properties"];

	for (auto p : geometry) {
		auto x = p["x"].get<float>();
		auto y = p["y"].get<float>();
		auto z = p["z"].get<float>();
		points.push_back(QVector3D(x, y, z));
	}

	for (auto p : properties.items()) {
		symbol->setProperty(p.key(), 
							p.value().type(), 
							p.value());
	}

	symbol->setGeometry(points);
	m_symbols[t_type] = std::make_unique<FSymbol>(symbol);
}

void BulkLoader::loadMany(json& t_json) {
	auto elements = t_json["symbols"];
	for (auto element : elements) {
		auto type = element["type"].get<std::string>();
		loadOne(type,element);
	}
}

BulkLoader::BulkLoader()
	: m_symbols() {}

void BulkLoader::load(std::string t_path) {
	std::ifstream t(t_path);
	std::string str((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());

	auto data = json::parse(str);
	auto type = data["type"].get<std::string>();
	if (type == "Collection") {
		loadMany(data);
	}
	else {
		loadOne(type, data);
	}
}

std::map<std::string, std::unique_ptr<FSymbol>>& BulkLoader::symbols() {
	return m_symbols;
}

FSymbol* BulkLoader::get(std::string t_name) {
	return m_symbols[t_name].get();
}

size_t BulkLoader::size() {
	return m_symbols.size();
}