#include "Game.h"
#include <FileSystem/FileSystem.h>
#include <Core/StringUtils.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <Math/Noise.h>
#include <Math/Random.h>

std::string Test = "$$\\      $$\\                     $$\\       $$\\             $$\\                $$$$$$\\  \n\
$$$\\    $$$ |                    $$ |      \\__|            $$ |              $$  __$$\\ \n\
$$$$\\  $$$$ | $$$$$$\\   $$$$$$\\  $$$$$$$\\  $$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\  \\__/  $$ |\n\
$$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |$$  _____|\\_$$  _|  $$  __$$\\  $$$$$$  |\n\
$$ \\$$$  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |$$ |\\$$$$$$\\    $$ |    $$ /  $$ |$$  ____/ \n\
$$ |\\$  /$$ |$$   ____|$$ |  $$ |$$ |  $$ |$$ | \\____$$\\   $$ |$$\\ $$ |  $$ |$$ |      \n\
$$ | \\_/ $$ |\\$$$$$$$\\ $$$$$$$  |$$ |  $$ |$$ |$$$$$$$  |  \\$$$$  |\\$$$$$$  |$$$$$$$$\\ \n\
\\__|     \\__| \\_______|$$  ____/ \\__|  \\__|\\__|\\_______/    \\____/  \\______/ \\________|\n\
                       $$ |                                                            \n\
                       $$ |                                                            \n\
                       \\__|\n\
----------------------------------------------------------------------------------------------------\n";

void RunTests()
{
#ifdef ENABLE_TESTCASES
	ME::Disk::internal::TestAll();
	ME::StringUtils::internal::TestAll();
#endif
}


int main(int argc, char** argv)
{
	std::cout << Test;
#if _DEBUG
	//spdlog::set_level(spdlog::level::debug);
	//RunTests();
#endif
	ME::Math::Noise MyNoise;
	ME::Random::Mersienne MyRandom;
	MyNoise.SetSeed(MyRandom.GetStartingSeed());
	MyNoise.SetBasicType(ME::Math::ENoiseType::OpenSimplex2S);

	auto file = std::string("Output.txt");
	std::filesystem::path filepath = ME::Disk::FromCurrentDirectory(file);
	std::fstream filestream;
	ME::Disk::FileCreate(filepath, filestream, true);
	std::string data = "";

	for (int i = 0; i < 256*256; i++)
	{
		string temp = "";
		Vec2<float> Coords = Vec2<float>(MyRandom.NextFloat(0.f, 1024.f), MyRandom.NextFloat(0.f, 1024.f));
		float x = MyNoise.GetNoise2D(Coords);
		ME::StringUtils::CastFrom(temp, x);
		data += temp + "\n";
	}
	filestream.write(data.c_str(), data.length());
}