#include "EnemyDebuffTower.h"

void EnemyDebuffTower::Initialize()
{
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::DeepPink));
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
}
