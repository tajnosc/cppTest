#include "TasksQueue.h"
#include "Thread.h"

TasksQueue::TasksQueue(std::uint16_t noOfThreads)
{
	for (int i = 0; i < noOfThreads; ++i)
	{
		threads.emplace_back(std::make_shared<Thread>(this));
	}
}

TasksQueue::~TasksQueue()
{
	shutdown = true;

	for (auto& thread : threads)
	{
		if (thread) {
			thread->Join();
		}
	}
}

void TasksQueue::Queue(Task anything)
{
	std::unique_lock lock{ mutex };

	tasks.push(anything);
	WakeUpIdleThread();
}

void TasksQueue::WakeUpIdleThread()
{
	for (auto& thread : threads)
	{
		if (thread && thread->WakeUp()) 
		{
			// Wake up the first idle thread
			return;
		}
	}
}

std::optional< Task > TasksQueue::GetTask()
{
	std::unique_lock lock{ mutex };

	if (!tasks.empty())
	{
		auto front = tasks.front();
		tasks.pop();
		return front;
	}

	return std::nullopt;
}