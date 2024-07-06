#include "UnitFactoryUI.h"
#include "Entity.h"
#include "UnitCard.h"
UnitCard* UnitFactoryUI::CreateUnitCard(int _unitID)
{
    UnitCard* entity = new UnitCard();
    entity->m_UnitID = _unitID;
    entity->SetUnitID(_unitID);
    /*switch (_unitID)
    {
    case 101:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
        break;
    case 102:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Brown));
        break;
    case 103:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::SpringGreen));
        break;
    case 104:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Snow));
        break;
    case 105:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::HotPink));
        break;
    case 115:
        entity->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
        break;

    default:
        SAFE_DELETE(entity);
        break;
    }*/
    
    return entity;
}
