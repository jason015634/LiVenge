#include "AttackObject.h"

AttackObject::AttackObject()
{
	AddComponent<BattleInfo>();
	AddComponent<Engine::Component::EffectAnimator>();
	AddComponent<Engine::Component::Transform>();
	AddComponent<UnitStatus>();
}

void AttackObject::Initialize()
{
}
