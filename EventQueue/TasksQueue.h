#include "Task.h"

#include <vector>
#include <atomic>
#include <queue>
#include <mutex>
#include <functional>
#include <optional>
#include <cstdint>

class Thread;

class TasksQueue
{
	std::vector< std::shared_ptr< Thread > > threads;

	std::mutex mutex;

	std::atomic<bool> shutdown{ false };

	std::queue< Task > tasks;

public:
	/*!
	 * \brief Creates a thread pool with no of threads passed
	 *        as an argument
	 */
	explicit TasksQueue( std::uint16_t noOfThreads );

	~TasksQueue();

	/*!
	 * \brief Queues task to be executed, wakes up idle threads (if available)
	 *        and returns immediately
	 */
	void Queue(Task anything);

	/*!
	 * \brief Pops a front task from the queue to be executed and returns it.
	 * 
	 * \return The front task to be executed, or std::nullopt when no task in the queue
	 */
	std::optional< Task > GetTask();

private:
	void WakeUpIdleThread();
};