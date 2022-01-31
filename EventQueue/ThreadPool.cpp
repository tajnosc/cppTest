#include "ThreadPool.h"
#include "Thread.h"

ThreadPool::ThreadPool(std::uint16_t noOfThreads)
{
	for (int i = 0; i < noOfThreads; ++i)
	{
		threads.emplace_back(std::make_shared<Thread>(this));
	}
}

ThreadPool::~ThreadPool()
{
	shutdown = true;

	for (auto& thread : threads)
	{
		if (thread) {
			thread->Join();
		}
	}
}

void ThreadPool::Queue(Task anything)
{
	std::unique_lock lock{ mutex };

	tasks.push(anything);
	WakeUpIdleThread();
}

void ThreadPool::WakeUpIdleThread()
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

std::optional< std::function<void()> > ThreadPool::GetTask()
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