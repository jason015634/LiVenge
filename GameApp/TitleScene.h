#pragma once
#include "../GameProcess/Scene.h"
class Camera;
class EditButton;
class GameEndButton;
class TitleScene : public Engine::Scene
{
public:
	TitleScene() {}
	~TitleScene() {}
public:

	void Initialize() override;
	void Finalize() override;

	void Start() override;
	void FixedUpdate() override;

	void Update() override;
	void LateUpdate() override;

private:
	Engine::Entity::Entity* m_pTitleBackground;
	Camera* m_pCamera;
	EditButton* m_pEditButton;
	GameEndButton* m_pGameEndButton;
};

