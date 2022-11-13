#include "App.h"

void App::Tick(float DeltaSeconds)
{

}

void App::PreInit()
{
	auto rect = WindowRect::GetDefault();
	Initialize("TestGame", rect, NULL);
}
