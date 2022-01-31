#include <string>
#include <cstdint>
#include <mutex>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>
#include <fstream>

class Logger
{
	struct Log
	{
		std::int64_t timestamp;
		std::string log;

		explicit Log(std::string log);
	};

	std::mutex m;
	std::vector< Log > logs;
	std::thread t;
	bool shutdown{ false };
	std::condition_variable cv;
	std::fstream file;

public:
	explicit Logger(const std::string& fileName);

	~Logger();

	void Log_message(std::string msg);

private:
	void LogAsync();

	void flush(std::vector< Log > logsToBePrinted);
};
