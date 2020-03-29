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
	auto symbol = FSymbol::from(t_type);
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

	symbol->setProperty("color", "Blue");

	symbol->setGeometry(points);

	if (m_symbols.count(t_type) > 0)
		delete m_symbols[t_type];

	m_symbols[t_type] = symbol;
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

BulkLoader::~BulkLoader() {
	for (auto sym : m_symbols) {
		delete sym.second;
	}
}

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

std::map<std::string, FSymbol*>& BulkLoader::symbols() {
	return m_symbols;
}

FSymbol* BulkLoader::getName(std::string t_name) {
	FSymbol* symbol = nullptr;
	for (auto s : m_symbols) {
		if (s.second->hasProperty("name",t_name)) {
			symbol = s.second;
		}
	}
	return symbol;
}

FSymbol* BulkLoader::get(std::string t_name) {
	if (m_symbols.count(t_name) > 0) {
		return m_symbols[t_name];
	}
	else {
		return nullptr;
	}
}

size_t BulkLoader::size() {
	return m_symbols.size();
}