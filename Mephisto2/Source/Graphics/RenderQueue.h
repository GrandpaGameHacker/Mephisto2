#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <Thread/Job.h>
#include <spdlog/spdlog.h>
#include <SDL2/SDL.h>

namespace ME::Graphics
{
	class RenderQueue
	{
	public:
		RenderQueue() : Queue(nullptr), GLContext(nullptr) {};

		RenderQueue(SDL_Window* Window) : Queue(nullptr), GLContext(nullptr)
		{
			Queue = std::make_unique<ME::Thread::JobQueue>();
			Execute([=] {
				GLContext = SDL_GL_CreateContext(Window); 
				WindowContext = Window;});
		};

		~RenderQueue()
		{
		};

		template <typename F, typename... Args,
			std::enable_if_t<std::is_invocable_v<F&&, Args &&...>, int> = 0>

		auto Execute(F&& function, Args &&... args)
		{
			return Queue->Execute(std::forward<F&&>(function), args...);
		}
		
		// Only use inside Execute([...] {...}) lambdas
		const SDL_GLContext GetContext();
		bool SetupOpenGL();
	protected:
		std::unique_ptr<ME::Thread::JobQueue> Queue;
		SDL_GLContext GLContext;
		SDL_Window* WindowContext;
	};

}
