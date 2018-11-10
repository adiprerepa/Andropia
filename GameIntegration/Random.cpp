#include "Random.h"
#include "Time.h"
#include <random>
#include <chrono>

const float Random::random()
{
	static std::mt19937 generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	static const float RANDOM_MAX_NUMBER = static_cast<float>(generator.max());

	return (generator() / RANDOM_MAX_NUMBER);
}
