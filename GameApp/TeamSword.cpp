#include "TeamSword.h"
void TeamSword::Initialize()
{
	AddComponent<Engine::Component::GameObject>();
	AddComponent<Engine::Component::FSM>();

	// 임시 렌더링용, 각 유닛마다 색상 다르게 지정
	// 이미지 생기면 이 컴포넌트 지워줄것
	AddComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Beige));
	// 이미 컴포넌트가 있으면 get컴포넌트처럼 쓸 수 있음
	// 컴포넌트가 비활성화 되어있다면 활성화시키니 주의!
	AddComponent<Engine::Component::Rectangle>()->SetRect(70,70);
	AddComponent<Engine::Component::Render>()->SetBitmapPath(L"..\\Resource/test.png");
	// 애니메이션 생길시 추가
	//AddComponent<Engine::Component::Animator>();
	//AddComponent<Engine::Component::Render>();
	AddComponent<Engine::Component::Transform>();
	AddComponent<BattleInfo>();
	AddComponent<UnitStatus>()->SetUnitStatus(101);
}
