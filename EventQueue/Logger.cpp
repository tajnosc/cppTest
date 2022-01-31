#include "Logger.h"

#include <chrono>
#include <utility>

Logger::Log::Log(std::string log):
	timestamp{ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() },
	log{ std::move(log) }
{
}

Logger::Logger(const std::string& fileName):
	file { std::fstream{ fileName,  std::fstream::app } }
{
	t = std::thread(&Logger::LogAsync, this);
}

Logger::~Logger()
{
	shutdown = true;
	cv.notify_one();

	if (t.joinable()) t.join();

	flush(logs);
}

void Logger::Log_message(std::string msg)
{
	{
		std::unique_lock<std::mutex> lck{ m };
		logs.emplace_back(std::move(msg));
	}
	cv.notify_one();
}

void Logger::LogAsync()
{
	while (!shutdown)
	{
		std::vector< Log > logsToBePrinted{};
		logsToBePrinted.reserve(logs.size()); // Expect that size might be the same
		{
			std::unique_lock<std::mutex> lck{ m };
			cv.wait_for(lck, std::chrono::milliseconds(100));
			std::swap(logs, logsToBePrinted);
		}

		flush(std::move(logsToBePrinted));
	}
}

void Logger::flush(std::vector< Log > logsToBePrinted)
{
	for (auto& log : logsToBePrinted)
	{
		file << "[" << std::to_string(log.timestamp) << "] " << std::move(log.log) << "\n";
	}
}