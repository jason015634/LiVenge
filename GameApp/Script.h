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
	// �ʼ� ������
public:

	static const ULONGLONG ComponentType = -1;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------�ʼ� ������---------------------
protected:
	Engine::SingletonManager* m_pTool = Engine::SingletonManager::GetInstance();

public:
};