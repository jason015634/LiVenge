#include "TeamDrain.h"
void TeamDrain::Initialize()
{
	AddComponent<Engine::Component::GameObject>();
	AddComponent<Engine::Component::FSM>();

	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Aquamarine));
	// �̹� ������Ʈ�� ������ get������Ʈó�� �� �� ����
	// ������Ʈ�� ��Ȱ��ȭ �Ǿ��ִٸ� Ȱ��ȭ��Ű�� ����!
	GetComponent<Engine::Component::Rectangle>()->SetRect(70, 70);

	// �ִϸ��̼� ����� �߰�
	//AddComponent<Engine::Component::Animator>();
	AddComponent<Engine::Component::Render>()->SetLayer(2);
	AddComponent<Engine::Component::Transform>();
	AddComponent<BattleInfo>();
	AddComponent<UnitStatus>()->SetUnitStatus(103);
}
