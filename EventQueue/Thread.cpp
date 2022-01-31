#include "Thread.h"
#include "ThreadPool.h"
#include "Task.h"

#include <optional>
#include <functional>

Thread::Thread(ThreadPool* pool) :
	pool{ pool } 
{
}

void Thread::ProcessTasks()
{
	std::optional< Task > task{ pool->GetTask() };

	while (task.has_value())
	{
		task.value()();
		task = pool->GetTask();
	}

	idle = true;
}

bool Thread::WakeUp()
{
	std::unique_lock lock{ m };

	if (!idle)
	{
		return false;
	}

	idle = false;

	t = std::thread(&Thread::ProcessTasks, this);

	return true;
}

void Thread::Join()
{
	if (t.joinable())
	{
		t.join();
	}
}