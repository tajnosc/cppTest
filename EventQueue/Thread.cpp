#include "Thread.h"
#include "TasksQueue.h"
#include "Task.h"

#include <optional>
#include <functional>

Thread::Thread(TasksQueue* queue) :
	queue{ queue } 
{
}

void Thread::ProcessTasks()
{
	std::optional< Task > task{ queue->GetTask() };

	while (task.has_value())
	{
		task.value()();
		task = queue->GetTask();
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