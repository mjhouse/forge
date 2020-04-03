#pragma once

#include <QtCore/QDir>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>

#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace resources {

	#define F_INVALID_PATH -1
	#define F_NO_ACCESS -2

	namespace {
		
		static fs::path m_root;

		std::string get_path(std::string t_directory, std::string t_file, bool t_require = false);
		
		std::string file_as_string(std::string t_directory, std::string t_file);

		QPixmap file_as_pixmap(std::string t_directory, std::string t_file);

		QByteArray file_as_bytes(std::string t_directory, std::string t_file);

	}

	/* Initialize
	   Find the root directory and init the resources map
	*/
	void initialize(std::string t_root);

	// overload for QString
	void initialize(QString t_root);

	/* Shader
	   Load a shader as a QByteArray
	*/
	QByteArray shader(QString t_file);

	/* Theme
	   Load a .qss file as a QString
	*/
	QString theme(QString t_file);

	/* Icon
	   Load an image as a QIcon
	*/
	QIcon icon(QString t_file);

	/* Data
	   Get a data file path
	*/
	std::string data(std::string t_name);

	/* Log
	   Get a log file path
	*/
	std::string log(std::string t_name);
}