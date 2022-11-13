#pragma once
#include <SDL2/SDL.h>
#include <Types.h>
#include <Graphics/RenderQueue.h>
#include <Threadpool/ThreadPool.h>
#include <Math/3D/Vector.inl>
struct WindowRect
{
	int x, y, width, height;
	inline static WindowRect GetDefault()
	{
		return { SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800, 600};
	}
};

constexpr uint32 DEFAULT_WINDOW_OPTIONS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

class IApplication
{
public:
	IApplication() : Rect(WindowRect::GetDefault())
	{};

	virtual ~IApplication() {};
	
	virtual bool Initialize(const std::string& Title, WindowRect& WinRect, uint32 flags);
	virtual void SetVisibility(bool bShow);
	virtual void Hide() { SetVisibility(false); };
	virtual void Show() { SetVisibility(true); };

	SDL_Window* GetWindow() const;
	std::string GetName() const;

	Vec2<int> GetScreenSize() const;
	Vec2<int> GetDrawableSize() const;

	float GetDeltaTime();
	float GetTimeSinceStart();
	bool IsRunning() const;
	bool IsValid() const;

	virtual void Begin();
	virtual void ResizeHandler(SDL_Event* event);
	virtual void EventLoop(SDL_Event* event);
	virtual void Tick(float DeltaSeconds) = 0;
	virtual void PreInit() = 0;

	static std::unique_ptr<ME::Graphics::RenderQueue> Renderer;
	static ThreadPool ThrdPool;

protected:
	long long FrameStart;
	SDL_Window* Window = nullptr;
	std::string Name;
	WindowRect Rect;
	uint32 flags = 0;
	bool bIsRunning = true;
	bool bIsValid = true;

};