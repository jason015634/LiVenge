#include "UnitCard.h"
#include "DataManager.h"
UnitCard::UnitCard()
{
    AddComponent<Engine::Component::UI>();
	AddComponent<Engine::Component::Transform>();
    AddComponent<Engine::Component::Collider>();
    GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
	/*AddComponent<Engine::Component::Rectangle>()->SetRect(92.5f, 115.f);
	GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Indigo));*/
	//GetComponent<Engine::Component::Rectangle>()->SetLayer(4);
    //AddComponent<Engine::Component::Render>()->SetBitmapPath(L"..\\Resource/UI_character_card_image.png");
    //GetComponent<Engine::Component::Render>()->SetLayer(2);

}

void UnitCard::Initialize()
{

}

void UnitCard::SetUnitID(int _unitID)
{
    m_UnitID = _unitID;
    if (DataManager::GetInstance().m_Card[_unitID] == nullptr)
    {

    }

    switch (m_UnitID)
    {
    case 101:
        //GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_card_image.png");
        GetComponent<Engine::Component::UI>()->SetBitmap(DataManager::GetInstance().m_Card[m_UnitID]);
        GetComponent<Engine::Component::UI>()->SetScale(1.03, 1.035, 1);
        GetComponent<Engine::Component::UI>()->SetLayer(2);
        m_UnitManaCost = DataManager::GetInstance().GetUnitMap()[_unitID].manaCost;
        break;
    case 102:
        //GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Brown));
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_card_image5.png");
        GetComponent<Engine::Component::UI>()->SetBitmap(DataManager::GetInstance().m_Card[m_UnitID]);
        GetComponent<Engine::Component::UI>()->SetScale(0.96, 1, 1);
        GetComponent<Engine::Component::UI>()->SetLayer(2);
        m_UnitManaCost = DataManager::GetInstance().GetUnitMap()[_unitID].manaCost;
        break;
    case 103:
        //GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::SpringGreen));
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_card_image4.png");
        GetComponent<Engine::Component::UI>()->SetBitmap(DataManager::GetInstance().m_Card[m_UnitID]);
        GetComponent<Engine::Component::UI>()->SetScale(0.96, 1, 1);
        GetComponent<Engine::Component::UI>()->SetLayer(2);
        m_UnitManaCost = DataManager::GetInstance().GetUnitMap()[_unitID].manaCost;
        break;
    case 104:
        //GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Snow));
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_card_image2.png");
        GetComponent<Engine::Component::UI>()->SetBitmap(DataManager::GetInstance().m_Card[m_UnitID]);
        GetComponent<Engine::Component::UI>()->SetScale(0.96, 1, 1);
        GetComponent<Engine::Component::UI>()->SetLayer(2);
        m_UnitManaCost = DataManager::GetInstance().GetUnitMap()[_unitID].manaCost;
        break;
    case 105:
        //GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::HotPink));
        GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_card_image3.png");
        GetComponent<Engine::Component::UI>()->SetBitmap(DataManager::GetInstance().m_Card[m_UnitID]);
        GetComponent<Engine::Component::UI>()->SetScale(0.96, 1, 1);
        GetComponent<Engine::Component::UI>()->SetLayer(2);
        m_UnitManaCost = DataManager::GetInstance().GetUnitMap()[_unitID].manaCost;
        break;
    }
}
