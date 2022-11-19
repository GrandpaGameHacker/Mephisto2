#include "Game.h"

#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

//////////////////////////////////////////////////////////////////////////
/* Test Case Includes *///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include <FileSystem/FileSystem.h>
#include <Assets/AssetLoader.h>
#include <Core/StringUtils.h>
//////////////////////////////////////////////////////////////////////////

#include <spdlog/spdlog.h>
#include <iostream>
#include "App.h"
void RunTests()
{
#ifdef ENABLE_TESTCASES
	ME::Disk::internal::TestAll();
	ME::StringUtils::internal::TestAll();
#endif
}

int main(int argc, char** argv)
{
	std::cout << EngineTitle;
#if _DEBUG
	spdlog::set_level(spdlog::level::debug);
	RunTests();
#endif
	AssetLoader myLoader;
	auto future_asset = myLoader.LoadAsync("/Assets/TestAsset.txt", ME::Disk::EFileMode::ASCII);
	auto asset = future_asset.get();
	SDL_SetMainReady();
	App application;
	application.Begin();
	application.~App();
	return 0;
};