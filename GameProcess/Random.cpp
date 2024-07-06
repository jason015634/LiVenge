#include "pch.h"
#include "Random.h"
#include <random>



Engine::Random::Random()
{
}

Engine::Random::~Random()
{
}

int Engine::Random::GetRandomNumber()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::discrete_distribution<size_t> distribution(0, 100);
    return m_RandomNumber;
}

int Engine::Random::GetRandomNumber(int _value)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, _value);
	return distribution(generator);
}

int Engine::Random::GetRandomNumber(const std::vector<std::pair<int, int*>>& vecProb)
{
	std::random_device rd;
	std::mt19937 generator(rd());

	std::vector<int> temp;
	for (const auto& pair : vecProb)
	{
		temp.push_back(*(pair.second));
	}

	//std::uniform_real_distribution<double> distribution(temp.cbegin(), temp.cend());
	std::discrete_distribution<size_t> d{ temp.cbegin(), temp.cend() };
	return vecProb[d(generator)].first;
}
