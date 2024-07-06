#include "EnemySword.h"

void EnemySword::Initialize()
{
	GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	GetComponent<Engine::Component::Transform>()->SetPosition(px *150,py*150);
}
