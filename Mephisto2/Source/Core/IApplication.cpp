#include "gl\glew.h"
#include <spdlog/spdlog.h>
#include "IApplication.h"

#include <Platform/Platform.h>
#include <Input/Keyboard.h>
#include <Input/Mouse.h>
#include <Input/IKeyboardListener.h>
#include <Input/IMouseListener.h>

#include <chrono>

std::unique_ptr<ME::Graphics::RenderQueue> IApplication::Renderer;
ThreadPool IApplication::ThrdPool;

bool IApplication::Initialize(const std::string& Title, WindowRect& WinRect, uint32 flags)
{
    ME::Platform::DPIScaling();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		spdlog::error("IApplication::Initialize()", "SDL_Init(SDL_INIT_EVERYTHING) failed!");
		bIsRunning = false;
		return false;
	}

    spdlog::info("IApplication::Initialize()", "SDL_INIT_SUCESS");

	Window = SDL_CreateWindow(
        Title.c_str(),
        WinRect.x, WinRect.y,
		WinRect.width, WinRect.height,
		flags | DEFAULT_WINDOW_OPTIONS);

    if (!Window)
    {
        spdlog::error("IApplication::Initialize()", "SDL_CreateWindow failed");
        bIsRunning = false;
        return false;
    }

    Renderer = std::make_unique<ME::Graphics::RenderQueue>(Window);
    Renderer->SetupOpenGL();
    return true;
}

void IApplication::SetVisibility(bool bShow)
{
}

SDL_Window* IApplication::GetWindow() const
{
    return Window;
}

std::string IApplication::GetName() const
{
    return Name;
}

Vec2<int> IApplication::GetScreenSize() const
{
	return Vec2<int>();
}

Vec2<int> IApplication::GetDrawableSize() const
{
	return Vec2<int>();
}

float IApplication::GetDeltaTime()
{
	typedef std::chrono::high_resolution_clock Time;
	static long long started = Time::now().time_since_epoch().count();
	long long now = Time::now().time_since_epoch().count();
	return static_cast<float>(now - started) / 1000000000.f;
}

bool IApplication::IsRunning() const
{
    return false;
}

bool IApplication::IsValid() const
{
    return false;
}

void IApplication::Begin()
{
    PreInit();
    while (bIsRunning)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            EventLoop(&event);
        }
        Tick(GetDeltaTime());

    }
}

void IApplication::ResizeHandler(SDL_Event* event)
{
}

void IApplication::EventLoop(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        bIsRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        Vec2<float> pos = Vec2<float>((float)event->button.x, (float)event->button.y);
        ME::Input::Mouse::Get()->TriggerButtonDownEvent(pos, event->button.button);
        break;
    }
}
