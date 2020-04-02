#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Resources.h"
#include "json.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

#define debug(m)   logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Debug, m);
#define info(m)    logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Info, m);
#define warning(m) logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Warning, m);
#define error(m)   logging::Logger::instance()->log(__FILE__, __LINE__, logging::LogLevel::Error, m);

#define STAMP_FORMAT "%Y%m%d"				// date format for filenames
#define DATE_FORMAT  "%Y-%m-%d %H:%M:%S"	// date format for logged messages
#define LEVEL_STR(l)  _log_map[(int)l]		// macro to map LogLevel to string

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
		Debug = 0,
		Info = 1,
		Warning = 2,
		Error = 3
	};

	class Logger {
	private:
		std::recursive_mutex m_lock;

		std::atomic<bool> m_run;

		std::thread m_writer;

		std::queue<json> m_messages;

		std::string m_path;

		std::ofstream m_file;

		Logger()
			: m_lock()
			, m_run(true)
			, m_writer(&Logger::write, this)
			, m_messages()
			, m_path()
			, m_file()
		{
			auto name = filename(STAMP_FORMAT);
			m_path = resources::log(name);
			m_file = std::ofstream(m_path, std::ios::app);
		}

		void write() {
			while (m_run.load()) {
				if (m_messages.size() > 0 && m_lock.try_lock()) {
					if (m_file.is_open()) {
						auto message = m_messages.front();
						m_file << message.dump() << std::endl;

						m_file.flush();
						m_messages.pop();
					}

					m_lock.unlock();
				}
			}
		}

		inline std::string stamp(const char* t_format) {
			auto tm = std::time(nullptr);
			auto lt = *std::localtime(&tm);

			std::ostringstream oss;
			oss << std::put_time(&lt, t_format);

			return oss.str();
		}

		inline std::string filename(const char* t_format) {
			std::ostringstream oss;

			oss << "forge-";
			oss << stamp(t_format);
			oss << ".log";

			return oss.str();
		}

	public:

		~Logger() {
			m_run.store(false);
			m_writer.join();
		}

		static Logger* instance() {
			static Logger logger;
			return &logger;
		}

		void log(const char*	t_file,
				 const int		t_line,
				 const LogLevel t_level,
				 const char*	t_message)
		{
			auto filename = fs::path(t_file)
				.filename()
				.string();

			json message = {
				{"file", filename},
				{"line", t_line},
				{"level", LEVEL_STR(t_level) },
				{"datetime", stamp(DATE_FORMAT) },
				{"message", t_message}
			};

			m_lock.lock();
			m_messages.push(message);
			m_lock.unlock();
		}

	};

}

#undef STAMP_FORMAT
#undef DATE_FORMAT
#undef LEVEL_STR

#endif // __LOGGER_H__