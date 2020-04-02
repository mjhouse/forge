#include "Resources.h"
#include "Exceptions.h"

namespace resources {

	namespace {

		std::string get_path(std::string t_directory, std::string t_file) {
			auto path = m_root / t_directory / t_file;
			return path.string();
		}
		
		void make_path(std::string t_directory) {
			auto path = m_root / t_directory;
			fs::create_directories(path);
		}

		std::string file_as_string(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file);
			std::ifstream file(path);

			if (!file.is_open())
				_throw(cannot_open_file,"Cannot read file to string");

			std::string data((std::istreambuf_iterator<char>(file)),
							  std::istreambuf_iterator<char>());

			return data;
		}

		QPixmap file_as_pixmap(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file);
			QPixmap image;

			if (!image.load(QString::fromStdString(path)))
				_throw(cannot_open_file,"Cannot read file to QPixmap");

			return image;
		}

		QByteArray file_as_bytes(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file);
			QFile file(QString::fromStdString(path));

			if (!file.open(QFile::ReadOnly))
				_throw(cannot_open_file,"Cannot read file to QByteArray");

			auto data = file.readAll();
			return data;
		}
	}

	// ------------------------------------------------------------------------
	// Public functions

	/* Initialize
	   Find the root directory and init the resources map
	*/
	void initialize(std::string t_root) {
		m_root = fs::absolute(fs::path(t_root));
		make_path("resources");
		m_root /= "resources";
	}

	void initialize(QString t_root) {
		initialize(t_root.toStdString());
	}

	/* Shader
	   Load a shader as a QByteArray
	*/
	QByteArray shader(QString t_file) {
		make_path("shaders");
		t_file = t_file.endsWith(".glsl") ? t_file : t_file + ".glsl";
		return file_as_bytes("shaders", t_file.toStdString());
	}

	/* Theme
	   Load a .qss file as a QString
	*/
	QString theme(QString t_file) {
		make_path("themes");
		t_file = t_file.endsWith(".qss") ? t_file : t_file + ".qss";
		return QLatin1String(file_as_bytes("themes", t_file.toStdString()));
	}

	QIcon icon(QString t_file) {
		make_path("images");
		t_file = t_file.endsWith(".png") ? t_file : t_file + ".png";
		return QIcon(file_as_pixmap("images", t_file.toStdString()));
	}

	std::string data(std::string t_name) {
		make_path("data");
		return get_path("data", t_name);
	}

	std::string log(std::string t_name) {
		make_path("logs");
		return get_path("logs", t_name);
	}

	// ------------------------------------------------------------------------

}