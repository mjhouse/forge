#include "Resources.h"

namespace resources {

	namespace {
		QString get_path(QString t_directory, QString t_file) {
			if (!paths.count(t_directory))
				throw F_INVALID_PATH;

			auto path = paths[t_directory].filePath(t_file);

			if (!QFile::exists(path))
				throw F_INVALID_PATH;

			return path;
		}

		std::string file_as_string(QString t_directory, QString t_file) {
			auto path = get_path(t_directory, t_file);

			std::ifstream t(path.toStdString());
			std::string data((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

			return data;
		}

		QPixmap file_as_pixmap(QString t_directory, QString t_file) {
			auto path = get_path(t_directory, t_file);
			return QPixmap(path);
		}

		QByteArray file_as_bytes(QString t_directory, QString t_file) {
			auto path = get_path(t_directory, t_file);
			QFile file(path);

			if (!file.open(QFile::ReadOnly))
				throw F_NO_ACCESS;

			return file.readAll();
		}
	}

	// ------------------------------------------------------------------------
	// Public functions

	/* Initialize
	   Find the root directory and init the resources map
	*/
	void initialize(QString t_root) {
		root = QDir(t_root);
		root.makeAbsolute();

		auto list = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		for (auto directory : list) {
			paths[directory] = root.filePath(directory);
		}
	}

	/* Shader
	   Load a shader as a QByteArray
	*/
	QByteArray shader(QString t_file) {
		t_file = t_file.endsWith(".glsl") ? t_file : t_file + ".glsl";
		return file_as_bytes("shaders", t_file);
	}

	/* Theme
	   Load a .qss file as a QString
	*/
	QString theme(QString t_file) {
		t_file = t_file.endsWith(".qss") ? t_file : t_file + ".qss";
		return QLatin1String(file_as_bytes("themes", t_file));
	}

	QIcon icon(QString t_file) {
		t_file = t_file.endsWith(".png") ? t_file : t_file + ".png";
		return QIcon(file_as_pixmap("images", t_file));
	}

	// ------------------------------------------------------------------------

}