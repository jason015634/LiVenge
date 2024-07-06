#pragma once
#include "../Component/Component.h"

typedef enum class E_CustomComponent : ULONGLONG
{
	UnitStatus = (ULONGLONG)Engine::Component::E_ComponentType::End,
	Tile,
	BattleInfo,
	MouseDragging,
};

class CustomComponent : public Engine::Component::Component
{

};