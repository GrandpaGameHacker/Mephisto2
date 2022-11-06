#pragma once
#include <functional>
#include <tuple>
#include <Core/MephistoAssert.h>
#include <any>
namespace ME::Thread
{
	static void SleepFor(uint64_t milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	class JobBase
	{
	public:
		JobBase() = default;
		virtual ~JobBase() {};
		virtual void Execute() = 0;
	};

	template <typename ...Args>
	class Job : public JobBase
	{
	protected:
		std::function<void()> CallableVoid;
		std::function<void(Args...)> CallableArgs;
		std::tuple<Args...> Parameters = {};
		bool bVoid = false;
		bool bBound = false;
	public:
		template<typename F, bool N = std::is_void<F>>
		Job(F&& function, Args&&... args)
		{
			MEPH_ASSERT(!N);
		};

		virtual ~Job() {}
		const bool IsBound() const { return bBound; }
		void Execute() override;
	};
}
