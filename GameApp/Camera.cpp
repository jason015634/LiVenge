#include "Camera.h"
#include "CameraScript.h"

void Camera::Initialize()
{
	AddComponent<Engine::Component::Camera>();
	AddComponent<Engine::Component::Transform>()->SetPosition(-285,680,0);
	AddComponent<Engine::Component::Collider>()->SetColliderInfo(1920.0f, 1080.0f);
	AddComponent<CameraScript>();
}