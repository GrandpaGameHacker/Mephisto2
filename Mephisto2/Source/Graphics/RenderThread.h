#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <spdlog/spdlog.h>

class RenderThread
{
public:
	RenderThread();
	~RenderThread();
	// add a safe-queue using std::move
protected:

};