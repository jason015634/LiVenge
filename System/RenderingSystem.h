#pragma once
#include "SystemBase.h"
#include <d2d1.h>
#pragma comment(lib,"d2d1.lib")


namespace Hide
{
	namespace Component
	{
		class AnimationAsset;
	}
}

namespace Engine
{
	namespace Component
	{
		class Animator;
	}

	namespace System
	{
		class D2DRenderer;

		class RenderingSystem : public SystemBase
		{
		public:
			RenderingSystem(D2DRenderer* _render) :
				m_pRenderer(_render)
			{}
			~RenderingSystem()
			{}
		public:
			bool Initialize(const std::vector<Entity::Entity*>* _entities) override;
			void Finalize() override;

			void SetEntity(Entity::Entity* _entity) override;
			void SetCamera(Entity::Entity* _Camera);
		public:
			virtual void FixedUpdate();
			virtual void Update();
			virtual void LateUpdate();
			void Render(ULONGLONG _time);

		private:
			D2DRenderer* m_pRenderer;
			Entity::Entity* m_pCamera;
			std::vector<Component::Animator*> m_AnimatorContainer;
			std::vector<Component::Rectangle*> m_RectangleContainer;
			std::vector<Component::Render*> m_RenderContainer;
			std::vector<Component::UI*> m_UIContainer;
			std::vector<Component::EffectAnimator*> m_EffectContainer;

		public:
			bool GetSharingAnimationAsset(const std::wstring _filePath, Hide::Component::AnimationAsset** _pAnimationAsset);
			bool GetSharingBitmap(const std::wstring _filePath, ID2D1Bitmap** _pBitmap);
			bool ReleaseSharingAnimationAsset(Hide::Component::AnimationAsset** _asset);
			bool ReleaseSharingBitmapFromFile(ID2D1Bitmap* _Bitmap);

		public:
			bool CreateSharingAnimationAsset(const std::wstring _filePath);
			bool CreateSharingAnimationAsset(const std::wstring _filePath, Hide::Component::AnimationAsset** _pAnimationAsset);
			bool CreateSharingBitmapFromFile(const std::wstring _filePath, ID2D1Bitmap** _pBitmap);

		private:
			std::map<std::wstring, Hide::Component::AnimationAsset*> m_SharingAnimationAssets;
			std::map<std::wstring, ID2D1Bitmap*> m_SharingBitmap;

			void CreateKenAsset(Hide::Component::AnimationAsset*);
		};
	}
}

