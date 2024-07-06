#include "WoodenFence.h"

void WoodenFence::Initialize()
{
	AddComponent<Engine::Component::GameObject>();
	AddComponent<Engine::Component::FSM>();

	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	//AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Beige));
	// �̹� ������Ʈ�� ������ get������Ʈó�� �� �� ����
	// ������Ʈ�� ��Ȱ��ȭ �Ǿ��ִٸ� Ȱ��ȭ��Ű�� ����!
	//AddComponent<Engine::Component::Rectangle>()->SetRect(70, 70);

	AddComponent<Engine::Component::Animator>();
	AddComponent<Engine::Component::Render>();
	AddComponent<Engine::Component::Transform>();
	AddComponent<BattleInfo>();
	AddComponent<UnitStatus>()->SetUnitStatus(301);
}
