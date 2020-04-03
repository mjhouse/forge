#include "Resources.h"
#include "Exceptions.h"

#define _ext(n,e) n.endsWith(e) ? t_file : t_file + e

namespace resources {

	namespace {

		inline std::string with_ext(QString t_name, const char* t_ext) {
			return (t_name.endsWith(t_ext) ? t_name : t_name + t_ext).toStdString();
		}

		std::string get_path(std::string t_directory, std::string t_file, bool t_require) {
			auto path = m_root / t_directory / t_file;
			
			if (t_require && !fs::exists(path))
				THROW(invalid_argument, "Path does not exist");

			return path.string();
		}

		std::string file_as_string(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file, true);
			std::ifstream file(path);

			if (!file.is_open())
				THROW(cannot_open_file,"Cannot read file to string");

			std::string data((std::istreambuf_iterator<char>(file)),
							  std::istreambuf_iterator<char>());

			return data;
		}

		QPixmap file_as_pixmap(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file, true);
			QPixmap image;

			if (!image.load(QString::fromStdString(path)))
				THROW(cannot_open_file,"Cannot read file to QPixmap");

			return image;
		}

		QByteArray file_as_bytes(std::string t_directory, std::string t_file) {
			auto path = get_path(t_directory, t_file, true);
			QFile file(QString::fromStdString(path));

			if (!file.open(QFile::ReadOnly))
				THROW(cannot_open_file,"Cannot read file to QByteArray");

			auto data = file.readAll();
			return data;
		}
	}

	/* Initialize
	   Find the root directory and init the resources map
	*/
	void initialize(std::string t_root) {
		m_root = fs::absolute(fs::path(t_root)) / "resources";
		fs::create_directories(m_root);
	}

	void initialize(QString t_root) {
		initialize(t_root.toStdString());
	}

	QByteArray shader(QString t_file) {
		fs::create_directories(m_root / "shaders");
		return file_as_bytes("shaders", with_ext(t_file, ".glsl"));
	}

	QString theme(QString t_file) {
		fs::create_directories(m_root / "themes");
		return QLatin1String(file_as_bytes("themes", with_ext(t_file,".qss")));
	}

	QIcon icon(QString t_file) {
		fs::create_directories(m_root / "images");
		return QIcon(file_as_pixmap("images", with_ext(t_file, ".png")));
	}

	std::string data(std::string t_name) {
		fs::create_directories(m_root / "data");
		return get_path("data", t_name);
	}

	std::string log(std::string t_name) {
		fs::create_directories(m_root / "logs");
		return get_path("logs", t_name);
	}

}