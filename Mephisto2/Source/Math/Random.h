#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <random>
#include <vector>
#include "../Types.h"

namespace ME
{
	namespace Random
	{
		/// <summary>
		/// A class implementing 64 bit unsigned PRNG Mersienne twister 1997
		/// </summary>
		class Mersienne
		{
		public:
			/// <summary>
			/// Default constructor, Generates default random seed based on time in nanoseconds.
			/// </summary>
			Mersienne();

			/// <summary>
			/// Specify a custom seed for random generation
			/// </summary>
			/// <param name="seed">the input seed for mt1997_64 random generation</param>
			Mersienne(uint64 seed);

			/// <summary>
			/// Get the next random 64 bit number
			/// </summary>
			/// <returns>64 bit random number</returns>
			uint64 Next();

			/// <summary>
			/// Get the next random 64 bit number within min/max
			/// </summary>
			/// <param name="max"> - maximum random number</param>
			/// <param name="min"> - minimum random number</param>
			/// <returns>A random 64 bit number between min and max</returns>
			uint64 Next(uint64 max, uint64 min);

			/// <summary>
			/// Get the next random float between min and max
			/// </summary>
			/// <param name="max"> - maximum random floating point number</param>
			/// <param name="min"> - minimum random floating point number</param>
			/// <returns>a random float between min and max</returns>
			float NextFloat(float max, float min);

			/// <summary>
			/// Get the next random double precision floating point between min and max
			/// </summary>
			/// <param name="max"> - maximum random double precision floating point number</param>
			/// <param name="min"> - minimum random double precision floating point number</param>
			/// <returns>a random double precision float between min and max</returns>
			double NextDouble(double max, double min);

			/// <summary>
			/// Skip the next 'n' PRNG generations
			/// </summary>
			/// <param name="n">number of generations to skip</param>
			void Skip(uint64 n);

			/// <summary>
			/// generate a vector of random 64 bit numbers
			/// </summary>
			/// <param name="n">how many random numbers to generate</param>
			/// <returns>a vector of random numbers</returns>
			std::vector<uint64> Next(uint64 n);

			/// <summary>
			/// generate a vector of random 64 bit integers between min/max
			/// </summary>
			/// <param name="n">how many random integers to generate</param>
			/// <param name="min">maximum random integer value</param>
			/// <param name="max">minimum random integer value</param>
			/// <returns>a vector of random integers between min/max</returns>
			std::vector<uint64> Next(uint64 n, uint64 min, uint64 max);

			/// <summary>
			/// generate a vector of random floats between min/max
			/// </summary>
			/// <param name="n"> - how many random floats to generate</param>
			/// <param name="max"> - maximum random float value</param>
			/// <param name="min"> - minimum random float value</param>
			/// <returns>a vector of random floats between min/max</returns>
			std::vector<float> NextFloat(uint64 n, float max, float min);

			/// <summary>
			/// generate a vector of random double precision floats between min/max
			/// </summary>
			/// <param name="n"> - how many random double precision floats to generate</param>
			/// <param name="max"> - maximum random double precision floats value</param>
			/// <param name="min"> - minimum random double precision floats value</param>
			/// <returns>a vector of random double precision floats between min/max</returns>
			std::vector<double> NextDouble(uint64 n, float max, float min);

			/// <summary>
			/// Get the original seed this PRNG was initialized with
			/// </summary>
			/// <returns>The PRNG original seed (either generated or supplied to constructor</returns>
			uint64 GetStartingSeed();

			/// <summary>
			/// Reseeds the PRNG engine to a new seed and resets the state.
			/// </summary>
			/// <param name="seed">the new seed to reset the PRNG to</param>
			void Reseed(uint64 seed);
		private:
			/// <summary>
			/// original seed
			/// </summary>
			uint64 Seed;
			std::mt19937_64 MT;
		};
	}
}
