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
	class RenderQueue : public ME::Thread::JobQueue
	{
	public:
		RenderQueue() {};
		~RenderQueue() {};
	};
}
