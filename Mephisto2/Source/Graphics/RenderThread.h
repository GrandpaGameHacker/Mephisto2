#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <Thread/Job.h>
#include <spdlog/spdlog.h>

namespace ME::Graphics
{
	class RenderThread
	{
	public:
		RenderThread();
		~RenderThread();
		// add a safe-queue using std::move
		template <typename... Args>
		inline void Execute(ME::Thread::Job<Args...> job)
		{
			std::scoped_lock lock(Mutex);

			std::shared_ptr<ME::Thread::JobBase> NewJob =
				std::shared_ptr<ME::Thread::Job<Args...>>
				(std::move(std::make_shared<ME::Thread::Job<Args...>>(std::move(job))));

			Jobs.push_back(DeferredJobs);
		}

		template <typename... Args>
		inline void ExecuteNow(ME::Thread::Job<Args...> job)
		{
			std::scoped_lock lock(Mutex);

			std::shared_ptr<ME::Thread::JobBase> NewJob =
				std::shared_ptr<ME::Thread::Job<Args...>>
				(std::move(std::make_shared<ME::Thread::Job<Args...>>(std::move(job))));
			Jobs.push_back(Jobs);

			while (Jobs.size() != 0)
			{
				ME::Thread::SleepFor(1);
			}
		}
	protected:
		void Render();
		std::mutex Mutex;
		std::thread Thread;
		std::vector<std::shared_ptr<ME::Thread::JobBase>> Jobs;
		std::vector<std::shared_ptr<ME::Thread::JobBase>> DeferredJobs;
		bool bStopAndExit = false;
	};
}
