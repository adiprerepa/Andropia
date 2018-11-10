#include "Random.h"
#include <chrono>

std::mt19937 Random::generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
