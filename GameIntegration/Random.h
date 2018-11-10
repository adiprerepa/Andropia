#pragma once
#include <random>

namespace Random
{
	extern std::mt19937 generator;

	const double dmax = generator._Max;
	const long long imax = generator._Max;

	inline long long randInt()
	{
		return generator();
	}

	inline double random()
	{
		return generator() / dmax;
	}

	template <typename I>
	I random_element(I begin, I end)
	{
		const unsigned long size = std::distance(begin, end) - 1;

		if (size)
			std::advance(begin, generator() % size);
		else
			return end;

		return begin;
	}
}