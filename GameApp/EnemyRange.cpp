#include "EnemyRange.h"

void EnemyRange::Initialize()
{
	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::HotPink));
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
}
