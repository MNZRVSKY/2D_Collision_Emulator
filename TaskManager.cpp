#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
	mFutures.clear();
	mThreads.clear();
}

void TaskManager::addTask(std::packaged_task<void()> task)
{
	std::lock_guard<std::mutex> lock(mMutex);

	mFutures.push_back(std::move(task.get_future()));

	std::thread thread(std::move(task));
	thread.join();

	mThreads.push_back(std::move(thread));

	std::list<std::thread>::iterator threadsIterator = mThreads.begin();
	std::list<std::future<void>>::iterator futuresIterator = mFutures.begin();

	// remove finished tasks
	while ( threadsIterator != mThreads.end() || futuresIterator != mFutures.end() )
	{
		auto status = futuresIterator->wait_for( std::chrono::seconds(0) );
		if (status == std::future_status::ready)
		{
			threadsIterator = mThreads.erase(threadsIterator);
			futuresIterator = mFutures.erase(futuresIterator);
		}
		else
		{
			++threadsIterator;
			++futuresIterator;
		}
	}
}
