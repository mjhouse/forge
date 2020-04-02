#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Resources.h"
#include "json.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <ctime>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

#define debug(m)   logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Debug, m);
#define info(m)    logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Info, m);
#define warning(m) logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Warning, m);
#define error(m)   logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Error, m);

namespace logging {

	// file-local array that maps log levels
	// to const char* representations
	namespace {
		const char* _log_map[] = {
			"Debug",
			"Info",
			"Warning",
			"Error"
		};
	}

	enum class LogLevel {
		Debug   = 0,
		Info    = 1,
		Warning = 2,
		Error   = 3
	};

	class Logger {
	private:
		std::recursive_mutex m_lock;

		std::atomic<bool> m_run;

		std::thread m_writer;

		std::queue<json> m_messages;

		std::string m_path;

		std::ofstream m_file;

		Logger();

		void push();

		void write();

		inline std::string stamp(const char* t_format) {
			auto tm = std::time(nullptr);
			auto lt = *std::localtime(&tm);

			std::ostringstream oss;
			oss << std::put_time(&lt, t_format);

			return oss.str();
		}

		inline std::string filename(const char* t_format) {
			std::ostringstream oss;

			oss << "forge-" 
				<< stamp(t_format) 
				<< ".log";

			return oss.str();
		}

	public:

		~Logger();

		static Logger* instance();

		void log(const char* t_file,
				 const int		t_line,
				 const LogLevel t_level,
				 const char* t_message);

	};

}

#endif // __LOGGER_H__