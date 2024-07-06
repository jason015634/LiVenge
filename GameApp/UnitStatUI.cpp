#include "UnitStatUI.h"
#include "DataManager.h"
UnitStatUI::UnitStatUI()
{
	AddComponent<Engine::Component::UI>();
	AddComponent<Engine::Component::Transform>();
	GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
    GetComponent<Engine::Component::UI>()->SetLayer(100);
}

void UnitStatUI::Initialize()
{

}

void UnitStatUI::SetUnitStatUI(int _ID)
{
	m_UnitID = _ID;

	switch (m_UnitID)
    {
	case 101:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Team_Sword.png");
        break;
    case 102:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Team_Arrow.png");
        break;
    case 103:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Team_Drain.png");
        break;
    case 104:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Team_Projectile.png");
        break;
    case 105:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Team_Summoner.png");
        break;
	case 201:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Enemy_Sword.png");
		break;
	case 202:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Enemy_Arrow.png");
		break;
	case 203:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Enemy_Range.png");
		break;
	case 204:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Enemy_Ballista.png");
		break;
	case 205:
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_UnitExplain_Enemy_DebuffTower.png");
		break;
}
}
