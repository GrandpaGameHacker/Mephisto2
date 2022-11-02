#include "Game.h"
#include <FileSystem/FileSystem.h>
#include <Core/StringUtils.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <Math/Noise.h>
#include <Math/Random.h>
#include <Graphics/RenderThread.h>

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
}