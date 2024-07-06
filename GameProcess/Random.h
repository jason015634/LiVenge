#pragma once

namespace Engine
{
	class Random
	{
		friend class SingletonManager;
	private:
		int m_MinNum = 1;
		int m_MaxNum = 100;
		int m_RandomNumber = 0;
	private:
		Random();
		~Random();

	public:
		int GetRandomNumber();
		int GetRandomNumber(int _value);

		int GetRandomNumber(const std::vector<std::pair<int, int*>>& vecProb);
	};
}


