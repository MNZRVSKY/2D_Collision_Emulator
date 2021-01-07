#pragma once

#include <mutex>
#include <future>
#include <thread>
#include <chrono>
#include <list>

class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	void addTask(std::packaged_task<void()> task);

private:
	static int id;
	std::mutex mMutex;
	std::list<std::thread> mThreads;
	std::list<std::future<void>> mFutures;
};

