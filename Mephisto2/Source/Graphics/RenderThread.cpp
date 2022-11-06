#include "RenderThread.h"

ME::Graphics::RenderThread::RenderThread() : Thread([=] { Render(); })
{}

ME::Graphics::RenderThread::~RenderThread()
{
	bStopAndExit = true;
	Thread.join();
}

void ME::Graphics::RenderThread::Render()
{
	while (!bStopAndExit)
	{
		{
			std::scoped_lock lock(Mutex);
			for (auto& job : Jobs)
			{
				job->Execute();
			}
			Jobs.clear();
		}
		std::vector<std::shared_ptr<ME::Thread::JobBase>> ThreadSafeJobs;
		{
			std::scoped_lock lock(Mutex);
			ThreadSafeJobs = std::move(DeferredJobs);
			DeferredJobs = std::vector<std::shared_ptr<ME::Thread::JobBase>>();
		}

		for (auto& job : ThreadSafeJobs)
		{
			job->Execute();
		}
		ThreadSafeJobs.clear();
		ME::Thread::SleepFor(1);
	}
}
