#include "EnemyRange.h"

void EnemyRange::Initialize()
{
	// 임시 렌더링용, 각 유닛마다 색상 다르게 지정
	// 이미지 생기면 이 컴포넌트 지워줄것
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::HotPink));
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
}
