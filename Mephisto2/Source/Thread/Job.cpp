#include "Job.h"

ME::Thread::JobQueue::JobQueue()
{
	ExecutorThread = std::thread([=]
		{
			Runner();
		});
}

ME::Thread::JobQueue::~JobQueue()
{
	bStopJobs = true;
	ExecutorThread.join();
}

void ME::Thread::JobQueue::Runner()
{
	while (true)
	{
		std::unique_lock<std::mutex> QueueLock(JobMutex, std::defer_lock);
		QueueLock.lock();
		JobCV.wait(QueueLock, [&]() -> bool
			{
				return !Jobs.empty() || bStopJobs;
			});

		if (bStopJobs)
			return;

		auto TempJob = std::move(Jobs.front());
		Jobs.pop();
		QueueLock.unlock();
		(*TempJob)();
	}
}
