#include "Logger.h"
#include "Task.h"
#include "ThreadPool.h"

int main()
{
	// The main question is how can I listen on a UNIX domain socket ( for events in the form of
	// strings in the standard JSON format. ), if I can't use any external libraries other than
	// c++ standard. So even POSIX can't be used.

	// In this project I created an even queue, where you can queue std::function

	Logger fileLogger{ "logs.txt" };
	Task eventTask = [&fileLogger] { fileLogger.Log_message("Task executed."); };
	
	constexpr std::uint16_t noOfThreads{ 4 };

	ThreadPool pool{ noOfThreads };

	pool.Queue(eventTask);
}