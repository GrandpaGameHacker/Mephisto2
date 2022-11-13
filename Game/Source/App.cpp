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
	spdlog::info("Mouse clicked at {},{}", position.X, position.Y);
}
