#include "pch.h"
#include "RenderingSystem.h"
#include "D2DRenderer.h"
#include "../Component/ComponentList.h"

using namespace Hide::Component;

bool Engine::System::RenderingSystem::Initialize(const std::vector<Entity::Entity*>* _entities)
{
	m_Entities.clear();
	m_AnimatorContainer.clear();
	m_RectangleContainer.clear();
	m_RenderContainer.clear();
	m_UIContainer.clear();

	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}
	
	return true;
}

void Engine::System::RenderingSystem::Finalize()
{
}

void Engine::System::RenderingSystem::SetEntity(Entity::Entity* _entity)
{
	ULONGLONG renderFlag = Component::Render::ComponentFlag | Component::Transform::ComponentFlag;
	ULONGLONG animatorFlag = Component::Animator::ComponentFlag;
	ULONGLONG rectFlag = Component::Transform::ComponentFlag | Component::Rectangle::ComponentFlag;
	ULONGLONG cameraFlag = Component::Transform::ComponentFlag | Component::Camera::ComponentFlag;
	ULONGLONG UIFlag = Component::UI::ComponentFlag;
	ULONGLONG effectAnimatorFlag = Component::EffectAnimator::ComponentFlag;

	if ((_entity->GetComponentFlag() & cameraFlag) == cameraFlag)
	{
		m_pCamera = _entity;
		return;
	}

	if ((_entity->GetComponentFlag() & renderFlag) == renderFlag)
	{
		m_Entities.push_back(_entity);
		if (_entity->GetComponent<Component::Render>()->GetBitmapPath()->size() > 1)
		{
			ID2D1Bitmap* bitmap = nullptr;
			GetSharingBitmap(*_entity->GetComponent<Component::Render>()->GetBitmapPath(),&bitmap);
			m_RenderContainer.push_back(_entity->GetComponent<Component::Render>());
			m_RenderContainer.back()->SetBitmap(bitmap);
		}
	}
	
	if ((_entity->GetComponentFlag() & animatorFlag) == animatorFlag)
	{
		m_AnimatorContainer.push_back(_entity->GetComponent<Component::Animator>());
		GetSharingBitmap(m_AnimatorContainer.back()->GetPath(), &m_AnimatorContainer.back()->m_AnimationAsset->pBitmap);
	}
	
	
	if ((_entity->GetComponentFlag() & rectFlag) == rectFlag)
	{
		m_RectangleContainer.push_back(_entity->GetComponent<Component::Rectangle>());
	}
	
	if ((_entity->GetComponentFlag() & UIFlag) == UIFlag)
	{
		ID2D1Bitmap* bitmap = nullptr;
		GetSharingBitmap(*_entity->GetComponent<Component::UI>()->GetBitmapPath(), &bitmap);
		m_UIContainer.push_back(_entity->GetComponent<Component::UI>());
		m_UIContainer.back()->SetBitmap(bitmap);
	}

	if ((_entity->GetComponentFlag() & effectAnimatorFlag) == effectAnimatorFlag)
	{
		m_EffectContainer.push_back(_entity->GetComponent<Component::EffectAnimator>());
		GetSharingBitmap(m_EffectContainer.back()->GetPath(), &m_EffectContainer.back()->m_AnimationAsset->pBitmap);
	}
}

void Engine::System::RenderingSystem::FixedUpdate()
{
}

void Engine::System::RenderingSystem::Update()
{
	
}

void Engine::System::RenderingSystem::Render(ULONGLONG _time)
{
	Component::Transform* transform;
	m_pRenderer->BeginRender();
	for (UINT i = 0; i <= Component::Render::GetMaxLayer(); i++)
	{
		for (auto entity : m_RectangleContainer)
		{
			if (entity->GetEntity()->GetActive() == false || entity->GetActive() == false)
			{
				continue;
			}
			transform = entity->GetEntity()->GetComponent<Component::Transform>();
			if (entity->GetActive() == false || entity->GetLayer() != i)
			{
				continue;
			}
			else
			{
				m_pRenderer->DrawFillRect(entity->GetRect(transform->GetScrrenTransform()), entity->GetColor(), entity->GetAlpha());
			}
		}

		for (auto entity : m_RenderContainer)
		{
			if (entity->GetEntity()->GetActive() == false || entity->GetActive() == false)
			{
				continue;
			}
			transform = entity->GetEntity()->GetComponent<Component::Transform>();
			if (entity->GetActive() == false || entity->GetLayer() != i)
			{
				continue;
			}
			else
			{
				if (entity->GetBitmap() == nullptr)
				{
					continue;
				}
				D2D1_SIZE_F size = entity->GetBitmapSize();
				transform->SetScaleOrigin(size.width/2,size.height);
				D2D1_RECT_F rc = { 0 + (entity->m_OffsetX), 0 + (entity->m_OffsetY), size.width + 0 + (entity->m_OffsetX) ,size.height + 0 + (entity->m_OffsetY) };
				m_pRenderer->DrawBitmap(entity->GetBitmap(), rc, rc, transform->GetScrrenTransform(), entity->GetEntity()->GetComponent<Component::Render>()->GetAlpha());
			}
		}
		for (auto entity : m_AnimatorContainer)
		{
			if (entity->GetEntity()->GetActive() == false || entity->GetActive() == false)
			{
				continue;
			}
			transform = entity->GetEntity()->GetComponent<Component::Transform>();
			if (entity->GetActive() == false || entity->GetLayer() != i)
			{
				continue;
			}
			else
			{
				// 프레임 바꿔주는 부분?
				entity->Play(_time);

				// 화면에 출력하는 부분
				transform->SetScaleOrigin(entity->GetBitmapSize().width / 2, entity->GetBitmapSize().height);
				m_pRenderer->DrawBitmap(entity->m_AnimationAsset->pBitmap, entity->GetDestRect(), entity->GetSrcRect(), transform->GetScrrenTransform(), entity->GetAlpha());
			}
		}
		for (auto entity : m_EffectContainer)
		{
			if (entity->GetEntity()->GetActive() == false || entity->GetActive() == false)
			{
				continue;
			}
			transform = entity->GetEntity()->GetComponent<Component::Transform>();
			if (entity->GetActive() == false || entity->GetLayer() != i)
			{
				continue;
			}
			else
			{
				entity->Play(_time);

				m_pRenderer->DrawBitmap(entity->m_AnimationAsset->pBitmap, entity->GetDestRect(), entity->GetSrcRect(), D2D1::Matrix3x2F::Scale(entity->GetScale().X, entity->GetScale().Y) * D2D1::Matrix3x2F::Rotation(entity->GetRotation()) * transform->GetScrrenTransform(), entity->GetAlpha());
			}
		}

	}
	for (UINT i = 0; i <= Component::Render::GetMaxLayer(); i++)
	{
		for (auto entity : m_UIContainer)
		{
			if (entity->GetEntity()->GetActive() == false || entity->GetActive() == false)
			{
				continue;
			}
			transform = entity->GetEntity()->GetComponent<Component::Transform>();
			if (entity->GetActive() == false || entity->GetLayer() != i)
			{
				continue;
			}
			else
			{

				if (entity->GetBitmap() == nullptr)
				{
					continue;
				}
				D2D1_SIZE_F size = entity->GetBitmap()->GetSize();
				//transform->SetScaleOrigin(size.width / 2, size.height / 2);
				D2D1_RECT_F destRect = {
					(0 + entity->m_OffsetX - size.width) / 2, 
					(0 + entity->m_OffsetY - size.height) / 2,
					(0 + entity->m_OffsetX - size.width) / 2 + size.width,
					(0 + entity->m_OffsetY - size.height) / 2 + size.height
				};
				D2D1_RECT_F srcRect = { (0 + entity->m_OffsetX - size.width) / 2, (0 + entity->m_OffsetY - size.height) / 2, size.width , size.height };
				if (entity->GetCameraAffect())
				{
					m_pRenderer->DrawBitmap(entity->GetBitmap(), destRect, srcRect, D2D1::Matrix3x2F::Scale(entity->GetScale().X, entity->GetScale().Y)* transform->GetScrrenTransform(), entity->GetAlpha());
				}
				else if (entity->GetCameraAffect() == false)
				{
					m_pRenderer->DrawBitmap(entity->GetBitmap(), destRect, srcRect, D2D1::Matrix3x2F::Scale(entity->GetScale().X, entity->GetScale().Y)* transform->GetWorldTransform(), entity->GetAlpha());
				}

				if (entity->GetEntity()->GetComponent<Engine::Component::Collider>() == nullptr)
				{
					continue;
				}
				else
				{
					//m_pRenderer->DrawFillRect(entity->GetEntity()->GetComponent<Engine::Component::Collider>()->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Red), 0.3f);
				}
			}
		}
	}

	m_pRenderer->EndRender();
}

void Engine::System::RenderingSystem::LateUpdate()
{
}

bool Engine::System::RenderingSystem::GetSharingAnimationAsset(const std::wstring _filePath, Hide::Component::AnimationAsset** _pAnimationAsset)
{
	if (m_SharingAnimationAssets[_filePath] != nullptr)
	{
		*_pAnimationAsset = m_SharingAnimationAssets[_filePath];

	}
	else
	{
		CreateSharingAnimationAsset(_filePath);
		*_pAnimationAsset = m_SharingAnimationAssets[_filePath];
	}
	//(*_pAnimationAsset)->AddRef();

	return false;
}

bool Engine::System::RenderingSystem::GetSharingBitmap(const std::wstring _filePath, ID2D1Bitmap** _pBitmap)
{
	/*if (m_SharingBitmap[_filePath] != nullptr)
	{
		_pBitmap = &m_SharingBitmap[_filePath];

	}
	else*/
	std::wstring ws = _filePath;
	if (ws.empty())
	{
		return false;
	}

	if(ws.find(L".png") != std::wstring::npos)
	{ }
	else
	{
		ws.append(L".png");
	}
	{
		CreateSharingBitmapFromFile(ws, _pBitmap);
	}
	(*_pBitmap)->AddRef();

	return true;
}

bool Engine::System::RenderingSystem::ReleaseSharingAnimationAsset(Hide::Component::AnimationAsset** _asset)
{
	return false;
}

bool Engine::System::RenderingSystem::ReleaseSharingBitmapFromFile(ID2D1Bitmap* _Bitmap)
{
	return false;
}

bool Engine::System::RenderingSystem::CreateSharingAnimationAsset(const std::wstring _filePath)
{
	return false;
}

bool Engine::System::RenderingSystem::CreateSharingAnimationAsset(const std::wstring _filePath, Hide::Component::AnimationAsset** _pAnimationAsset)
{
	AnimationAsset* result = new AnimationAsset;
	GetSharingBitmap(_filePath, &result->pBitmap);

	if (_filePath == L"C:\\Users\\User\\Documents\\GitHub\\Yongs2DEngine\\Resource\\ken.png")
	{
		CreateKenAsset(result);
	}
	m_SharingAnimationAssets[_filePath] = result;
	return false;
}

bool Engine::System::RenderingSystem::CreateSharingBitmapFromFile(const std::wstring _filePath, ID2D1Bitmap** _pBitmap)
{
	m_pRenderer->CreateD2DBitmapFromFile(_filePath.c_str(), _pBitmap);
	//m_SharingBitmap[_filePath] = *_pBitmap;
	return true;
}

void Engine::System::RenderingSystem::CreateKenAsset(Hide::Component::AnimationAsset* _pAnimationAsset)
{
	AnimationInfo animation;
	animation.frameInfo.clear();
	animation.frameInfo.push_back(FrameInfo(3, 698, 61, 787, 0.1f));
	animation.frameInfo.push_back(FrameInfo(73, 696, 130, 787, 0.1f));
	animation.frameInfo.push_back(FrameInfo(143, 695, 197, 787, 0.1f));
	animation.frameInfo.push_back(FrameInfo(279, 698, 337, 787, 0.1f));
	animation.frameInfo.push_back(FrameInfo(347, 699, 406, 787, 0.1f));
	_pAnimationAsset->animations[L"Idle"] = animation;

	animation.frameInfo.clear();
	animation.frameInfo.push_back(FrameInfo(9, 883, 61, 965, 0.1f));
	animation.frameInfo.push_back(FrameInfo(71, 878, 130, 965, 0.1f));
	animation.frameInfo.push_back(FrameInfo(141, 877, 204, 966, 0.1f));
	animation.frameInfo.push_back(FrameInfo(216, 876, 278, 964, 0.1f));
	animation.frameInfo.push_back(FrameInfo(358, 878, 407, 966, 0.1f));
	_pAnimationAsset->animations[L"Move"] = (animation);

	animation.frameInfo.clear();
	animation.frameInfo.push_back(FrameInfo(731, 1685, 805, 1775, 0.05f));
	animation.frameInfo.push_back(FrameInfo(809, 1685, 890, 1772, 0.05f));
	animation.frameInfo.push_back(FrameInfo(896, 1679, 955, 1773, 0.05f));
	animation.frameInfo.push_back(FrameInfo(966, 1674, 1079, 1772, 0.05f));
	animation.frameInfo.push_back(FrameInfo(1101, 1679, 1201, 1772, 0.05f));
	animation.frameInfo.push_back(FrameInfo(1223, 1677, 1295, 1771, 0.05f));
	animation.frameInfo.push_back(FrameInfo(1302, 1677, 1373, 1771, 0.05f));
	animation.frameInfo.push_back(FrameInfo(1400, 1680, 1473, 1777, 0.05f));
	_pAnimationAsset->animations[L"Attack"] = (animation);
}
