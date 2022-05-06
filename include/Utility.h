#pragma once
#include <random>

class Utility
{
public:
	static float GetRandomFloat(float range1, float range2)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> getrand(range1, range2);
		return getrand(gen);
	}

	static float GetRandomFloat(float range)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> getrand2(0, range);
		return getrand2(gen);
	}

	static float constrain(float value, float min, float max)
	{
		if (value > max) return max;
		if (value < min) return min;

		return value;
	}
};