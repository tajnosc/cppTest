#pragma once

#include <random>

class RandomEngine
{
public:
	static std::mt19937& Get()
	{
		static RandomEngine instance;
		return instance.engine;
	}

private:
	RandomEngine() = default;

	std::random_device dev;
	std::mt19937       engine{ dev() };
};
