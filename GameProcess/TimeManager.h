#pragma once
#include "framework.h"
#include "IManager.h"

namespace Engine
{
	class TimeManager : public IManager
	{
		friend class SingletonManager;
	private:
		TimeManager();
		~TimeManager() {};
	private:
		bool Initialize() override final;
		void Finalize() override final;

	private:
		
		void Update();
	public:
		const ULONGLONG& GetDeltaTime()
		{
			return m_DeltaTime;
		}


	private:
		ULONGLONG m_DeltaTime;
		ULONGLONG m_CurrTime;
		ULONGLONG m_PrevTIme;
	};

}

