#include "Player.h"
Player* Player::Instance = nullptr;


Player::Player()
{
    AddComponent<Engine::Component::GameObject>()->SetTag(L"Player");
    AddComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_health_bar_image.png");
    GetComponent<Engine::Component::UI>()->SetLayer(2);
    GetComponent<Engine::Component::UI>()->SetCameraAffect(false);
    AddComponent<Engine::Component::Transform>()->SetPosition(150.f, 150.f, 0);
    SetPlayer();
}

Player::~Player()
{
}

void Player::Initialize()
{ 
}


