#include "EnemyArrow.h"

void EnemyArrow::Initialize()
{
	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Pink));
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
}
