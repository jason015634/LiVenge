#include "Unit.h"
#include "LogicAnimation.h"
#include "BattleScript.h"
#include "DataManager.h"
#include "MouseDragging.h"
Unit::Unit()
{
	AddComponent<Engine::Component::GameObject>();

	// �ӽ� ��������, �� ���ָ��� ���� �ٸ��� ����
	// �̹��� ����� �� ������Ʈ �����ٰ�
	//AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	// �̹� ������Ʈ�� ������ get������Ʈó�� �� �� ����
	// ������Ʈ�� ��Ȱ��ȭ �Ǿ��ִٸ� Ȱ��ȭ��Ű�� ����!
	//GetComponent<Engine::Component::Rectangle>()->SetRect(70, 70);

	// �ִϸ��̼� ����� �߰�
	AddComponent<Engine::Component::Animator>();
//	AddComponent<Engine::Component::Animator>()->SetOffset(-100,-150);

	AddComponent<Engine::Component::EffectAnimator>();
	GetComponent<Engine::Component::EffectAnimator>()->SetResourcePath(DataManager::GetInstance().m_EffectDatas[0].m_Path);
	GetComponent<Engine::Component::EffectAnimator>()->m_AnimationAsset = &DataManager::GetInstance().m_EffectDatas[0];
	GetComponent<Engine::Component::EffectAnimator>()->SetLayer(100);


	AddComponent<Engine::Component::Render>();
	AddComponent<Engine::Component::Transform>();
	AddComponent<Engine::Component::Collider>()->SetColliderInfo(GetComponent<Engine::Component::Animator>()->GetBitmapSize().width, GetComponent<Engine::Component::Animator>()->GetBitmapSize().height);

	AddComponent<BattleInfo>();
	AddComponent<UnitStatus>();
	AddComponent<LogicAnimation>();
	AddComponent<MouseDragging>();
	AddComponent<BattleScript>();
}

void Unit::Initialize()
{
	GetComponent<Engine::Component::Animator>()->SetLayer(4);
	GetComponent<Engine::Component::Transform>()->SetPosition(px * 150, py * 150);
	GetComponent<BattleInfo>()->SetFieldPosition(px,py);
}
