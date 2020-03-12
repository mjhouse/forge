#pragma once

#include <QtCore/QDir>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>

#include <map>
#include <iostream>
#include <fstream>

namespace resources {

	#define F_INVALID_PATH -1
	#define F_NO_ACCESS -2

	namespace {
		
		static QDir root;

		static std::map<QString, QDir> paths;

		QString get_path(QString t_directory, QString t_file);

		std::string file_as_string(QString t_directory, QString t_file);

		QPixmap file_as_pixmap(QString t_directory, QString t_file);

		QByteArray file_as_bytes(QString t_directory, QString t_file);

	}

	// ------------------------------------------------------------------------
	// Public functions

	/* Initialize
	   Find the root directory and init the resources map
	*/
	void initialize(QDir t_root);

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

	// ------------------------------------------------------------------------
}