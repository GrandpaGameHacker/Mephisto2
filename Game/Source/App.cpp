#include "App.h"

void App::Tick(float DeltaSeconds)
{

}

void App::PreInit()
{
	auto rect = WindowRect::GetDefault();
	Initialize("TestGame", rect, NULL);
}

void App::OnMouseButtonDown(const Vec2<float>& position, int button)
{
	spdlog::info("[Delta {} ]Mouse clicked at {},{}", GetDeltaTime(), position.X, position.Y);
	spdlog::info("Button was : {}", button);
}

void App::OnKeyDown(int key)
{
	spdlog::info("Key pressed for application listener : {}", key);
}

void App::OnMouseWheel(const Vec2<float>& position, const Vec2<float>& ScrollAmount)
{
	spdlog::info("mouse scrolled for application listener : {}, {}", ScrollAmount.X, ScrollAmount.Y);
}
