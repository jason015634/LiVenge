#pragma once
#include "../Component/ScriptComponent.h"
#include "../GameProcess/SingletonManager.h"
#include "Entity.h"

class Script : public Engine::Component::ScriptComponent
{
public:
	Script()
	{
	}
	virtual ~Script()
	{}
	// 필수 구현부
public:

	static const ULONGLONG ComponentType = -1;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------필수 구현부---------------------
protected:
	Engine::SingletonManager* m_pTool = Engine::SingletonManager::GetInstance();

public:
};