#include "Logger.h"
#include "Resources.h"

#define STAMP_FORMAT "%Y%m%d"				// date format for filenames
#define DATE_FORMAT  "%Y-%m-%d %H:%M:%S"	// date format for logged messages
#define LEVEL_STR(l)  _log_map[(int)l]		// macro to map LogLevel to string

namespace logging {

	Logger::Logger()
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
	
	Logger::~Logger() {
		m_run.store(false);
		m_writer.join();
	}

	void Logger::push() {
		auto message = m_messages.front();
		m_file << message.dump() << std::endl;
		m_messages.pop();
	}

	void Logger::write() {
		// Loop until m_run is false. On every iteration, try to 
		// lock the message queue, and if there are messages 
		// waiting, push them to the log file.
		while (m_run.load()) {
			if (m_messages.size() > 0 && m_lock.try_lock()) {
				if (m_file.is_open()) {
					push();
					m_file.flush();
				}

				m_lock.unlock();
			}
		}

		// On exit, lock the message queue, and if the file
		// is open, write all waiting messages to the log
		// file. Close the log file and unlock the queue.
		m_lock.lock();
		if (m_file.is_open()) {
			while (!m_messages.empty()) {
				push();
			}
			m_file.flush();
			m_file.close();
		}
		m_lock.unlock();
	}

	Logger* Logger::instance() {
		static Logger logger;
		return &logger;
	}

	void Logger::log(
		const char*    t_file,
		const int	   t_line,
		const LogLevel t_level,
		const char*    t_message)
	{
		auto filename = fs::path(t_file)
			.filename()
			.string();

		json message = {
			{"file",     filename},
			{"line",     t_line},
			{"level",    LEVEL_STR(t_level) },
			{"datetime", stamp(DATE_FORMAT) },
			{"message",  t_message}
		};

		m_lock.lock();
		m_messages.push(message);
		m_lock.unlock();
	}

}

#undef STAMP_FORMAT
#undef DATE_FORMAT
#undef LEVEL_STR