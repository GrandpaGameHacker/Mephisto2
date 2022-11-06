#pragma once
#include <functional>
#include <tuple>
#include <queue>
#include <future>
#include <Core/MephistoAssert.h>

namespace ME::Thread
{
	static void SleepFor(uint64_t milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	class JobContainerBase
	{
	public:
		JobContainerBase() = default;
		virtual ~JobContainerBase() {};
		virtual void operator()() = 0;
	};
	using _JobPointer = std::unique_ptr<JobContainerBase>;

	template <typename F, std::enable_if_t<std::is_invocable_v<F&&>, int> = 0>
	class Job : public JobContainerBase
	{
	public:
		Job(F&& func) : _f(std::forward<F>(func)) {};
		virtual ~Job() {}
		void operator ()() override { _f(); }

	protected:
		F _f;
	};

	class JobQueue
	{
	public:
		JobQueue();
		virtual ~JobQueue();
		template <typename F, typename... Args,
			std::enable_if_t<std::is_invocable_v<F&&, Args &&...>, int> = 0>

		auto Execute(F&& function, Args &&... args)
		{
			std::unique_lock<std::mutex> QueueLock(JobMutex, std::defer_lock);
			std::packaged_task<std::invoke_result_t<F, Args...>()> JobPackage(
				[_f = std::move(function),
				_fargs = std::make_tuple(std::forward<Args>(args)...)]() mutable
				{
					return std::apply(std::move(_f), std::move(_fargs));
				});
			std::future<std::invoke_result_t<F, Args...>> Future = JobPackage.get_future();

			QueueLock.lock();

			Jobs.emplace(_JobPointer(new Job([task(std::move(JobPackage))]() mutable { task(); })));

			QueueLock.unlock();

			JobCV.notify_one();

			return std::move(Future);
		}
	private:
		void Runner();
	protected:
		std::thread ExecutorThread;
		std::queue<_JobPointer> Jobs;
		std::mutex JobMutex;
		std::condition_variable JobCV;
		bool bStopJobs = false;
	};
}
