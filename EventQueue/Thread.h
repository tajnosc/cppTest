#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

class ThreadPool;

class Thread
{
	ThreadPool* pool;

	std::atomic<bool> idle{ true };

	std::thread t;

	std::mutex m;

public:
	explicit Thread(ThreadPool* pool);

	/*!
	 * \brief Trigger thread to wake up and fetch tasks from the thread pool
	 *		  to be executed
	 */
	bool WakeUp();

	/*!
	 * \brief Joins the thread
	 */
	void Join();

private:
	void ProcessTasks();
};