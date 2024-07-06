#pragma once
#include "InputManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "Random.h"

namespace Engine
{
	class SingletonManager
	{
		friend class GameProcess;
	private:
		SingletonManager()
		{}
		~SingletonManager()
		{}
		static SingletonManager* m_pInstance;
	public:
		static SingletonManager* GetInstance()
		{
			if (m_pInstance == nullptr)
			{
				m_pInstance = new SingletonManager();
			}
			return m_pInstance;
		}

	private:
		void Initialize(HWND _hWnd);
		void Finalize();
		void Update();

	public:
		InputManager m_Input;
		TimeManager m_Time;
		Random m_Random;
	//	SoundManager m_Sound;

	private:
		HWND m_hWnd;

	};
}