#pragma once
#include "../System/SystemBase.h"
#include "../GameProcess/SingletonManager.h"
#include "ComponentList.h"

class System : public Engine::System::SystemBase
{
public:
	System() {};
	virtual ~System() {};
protected:
	Engine::SingletonManager* m_pTool = Engine::SingletonManager::GetInstance();
};

