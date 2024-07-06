#include "Unit.h"
#include "LogicAnimation.h"
#include "BattleScript.h"
#include "DataManager.h"
#include "MouseDragging.h"
Unit::Unit()
{
	AddComponent<Engine::Component::GameObject>();

	// 임시 렌더링용, 각 유닛마다 색상 다르게 지정
	// 이미지 생기면 이 컴포넌트 지워줄것
	//AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	// 이미 컴포넌트가 있으면 get컴포넌트처럼 쓸 수 있음
	// 컴포넌트가 비활성화 되어있다면 활성화시키니 주의!
	//GetComponent<Engine::Component::Rectangle>()->SetRect(70, 70);

	// 애니메이션 생기면 추가
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
