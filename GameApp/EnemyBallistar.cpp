#include "EnemyBallistar.h"

void EnemyBallistar::Initialize()
{
	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::GreenYellow));
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
}
