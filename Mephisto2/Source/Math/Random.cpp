#include "Random.h"
#include <chrono>
ME::Random::Mersienne::Mersienne()
{
    Seed = std::chrono::high_resolution_clock::now().time_since_epoch().count() ^ 69 ^ rand();
    MT = std::mt19937_64(Seed);
}

ME::Random::Mersienne::Mersienne(uint64 seed)
{
    Seed = seed;
    MT = std::mt19937_64(Seed);
}

uint64 ME::Random::Mersienne::Next()
{
    return MT();
}

uint64 ME::Random::Mersienne::Next(uint64 max, uint64 min)
{
    auto number = MT();
    number = min + (max - min) * (number / 0xffffffffffffffff);
    return number;
}

float ME::Random::Mersienne::NextFloat(float max, float min)
{
    float number = MT();
    number = min + (max - min) * (number / 0xffffffffffffffff);
    return number;
}

double ME::Random::Mersienne::NextDouble(double max, double min)
{
    double number = MT();
	number = min + (max - min) * (number / 0xffffffffffffffff);
	return number;
}

void ME::Random::Mersienne::Skip(uint64 n)
{
    MT.discard(n);
}

std::vector<uint64> ME::Random::Mersienne::Next(uint64 n)
{
    std::vector<uint64> RandomNumbers;
    for (uint64 i = 0; i < n; i++) {
        RandomNumbers.push_back(MT());
    }
    return RandomNumbers;
}

std::vector<uint64> ME::Random::Mersienne::Next(uint64 n, uint64 min, uint64 max)
{
	std::vector<uint64> RandomNumbers;
	for (uint64 i = 0; i < n; i++)
	{
		RandomNumbers.push_back(Next(min, max));
	}
	return RandomNumbers;
}

std::vector<float> ME::Random::Mersienne::NextFloat(uint64 n, float max, float min)
{
	std::vector<float> RandomNumbers;
	for (uint64 i = 0; i < n; i++) {
		RandomNumbers.push_back(NextFloat(max, min));
	}
	return RandomNumbers;
}

std::vector<double> ME::Random::Mersienne::NextDouble(uint64 n, float max, float min)
{
	std::vector<double> RandomNumbers;
	for (uint64 i = 0; i < n; i++) {
		RandomNumbers.push_back(NextFloat(max, min));
	}
	return RandomNumbers;
}

uint64 ME::Random::Mersienne::GetStartingSeed()
{
	return Seed;
}

void ME::Random::Mersienne::Reseed(uint64 seed)
{
	MT.seed(seed);
}