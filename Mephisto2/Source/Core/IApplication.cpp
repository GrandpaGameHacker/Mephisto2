#include "gl\glew.h"
#include <spdlog/spdlog.h>
#include "IApplication.h"

#include <Platform/Platform.h>
#include <Input/Keyboard.h>
#include <Input/Mouse.h>
#include <Input/IKeyboardListener.h>
#include <Input/IMouseListener.h>
#include <Graphics/ImGuiBackend/imgui_impl_sdl.h>

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
    Renderer->SetupImGui();
    GetTimeSinceStart();
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
	long long now = Time::now().time_since_epoch().count();
	return static_cast<float>(now - FrameStart) / 1000000000.f;
}

float IApplication::GetTimeSinceStart()
{
	typedef std::chrono::high_resolution_clock Time;
    static long long start = Time::now().time_since_epoch().count();
	long long now = Time::now().time_since_epoch().count();
	return static_cast<float>(now - start) / 1000000000.f;
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
        typedef std::chrono::high_resolution_clock Time;
        FrameStart = Time::now().time_since_epoch().count();
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            EventLoop(&event);
        }
        ME::Input::Mouse::Get()->OnStartFrame();
        ME::Input::Keyboard::Get()->OnStartFrame();
        Renderer->NewFrame();
        Tick(GetDeltaTime());
        Renderer->Swap();
        ME::Thread::SleepFor(1);
    }
	Renderer.reset();
	ThrdPool.~thread_pool();
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void IApplication::ResizeHandler(SDL_Event* event)
{
}

void IApplication::EventLoop(SDL_Event* event)
{
    Vec2<float> pos;
    Vec2<float> scrollAmount;
    Renderer->ImGuiProcessEvent(event);
    switch (event->type)
    {
    case SDL_QUIT:
        bIsRunning = false;
        break;

    case SDL_MOUSEBUTTONDOWN:
        pos = Vec2<float>((float)event->button.x, (float)event->button.y);
        ME::Input::Mouse::Get()->TriggerButtonDownEvent(pos, event->button.button);
        break;

    case SDL_MOUSEBUTTONUP:
		pos = Vec2<float>((float)event->button.x, (float)event->button.y);
		ME::Input::Mouse::Get()->TriggerButtonUpEvent(pos, event->button.button);
		break;

    case SDL_MOUSEMOTION:
		pos = Vec2<float>((float)event->motion.x, (float)event->motion.y);
		ME::Input::Mouse::Get()->TriggerMoveEvent(pos);
        break;

    case SDL_MOUSEWHEEL:
        int x, y;
        scrollAmount = Vec2<float>(event->wheel.preciseX, event->wheel.preciseY);
        SDL_GetMouseState(&x, &y);
        pos = Vec2<float>((float)x, (float)y);
		ME::Input::Mouse::Get()->TriggerScrollwheelEvent(pos, scrollAmount);
        break;

    case SDL_KEYDOWN:
        ME::Input::Keyboard::Get()->TriggerKeyDownEvent(event->key.keysym.scancode);
        break;

    case SDL_KEYUP:
		ME::Input::Keyboard::Get()->TriggerKeyUpEvent(event->key.keysym.scancode);
    }
}
