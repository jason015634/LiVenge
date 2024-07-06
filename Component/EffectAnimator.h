#pragma once
#include "RenderingComponent.h"
#include "Animator.h"

namespace Engine
{
	namespace Component
	{
		class EffectAnimator : public RenderingComponent
		{
		public:
			EffectAnimator()
			{
				SetActive(false);
			}
			// 필수 작성부
		public:
			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::EffectAnimator;
			static const ULONGLONG ComponentFlag = 1 << ComponentType;
			//-------------------------------

		public:
			// 시스템에서 쓰는 함수
			void SetState(std::wstring _state) { m_AnimationName = _state; }
			void Play(ULONGLONG _time);
			const std::wstring& GetPath() { return m_Path; }
			void SetResourcePath(std::wstring _path) { m_Path = _path; }
			const D2D1_RECT_F& GetDestRect() { return m_DestRect; }
			const D2D1_RECT_F& GetEffectRect() { return m_EffectRect; }
			void SetEffectRect(float _x, float _y)
			{
				m_EffectRect = m_DestRect;
				m_EffectRect.left += _x;
				m_EffectRect.right += _x;
				m_EffectRect.top += _y;
				m_EffectRect.bottom += _y;
			}
			const D2D1_RECT_F& GetSrcRect() { return m_SrcRect; }
			const D2D1_SIZE_F GetBitmapSize()
			{
				return{ m_DestRect.right,m_DestRect.bottom };
			}
			std::wstring GetAnimName()
			{
				return m_AnimationName;
			}
			void SetBitmap(ID2D1Bitmap* _bitmap) override
			{
				m_AnimationAsset->pBitmap = _bitmap;
			}
			void PlayEffect()
			{
				SetActive(true);
				m_CurrFrameIndex = 0;
			}
			void SetSpeed(float _speed) { m_Speed = _speed; }

			void SetScale(float _x, float _y, float _z)
			{
				m_Scale.X = _x;
				m_Scale.Y = _y;
				m_Scale.Z = _z;
			}


			Vector3 GetScale()
			{ 
				return m_Scale;
			}

			void SetRotation(float _rotation)
			{
				m_Rotation = _rotation;
			}

			float GetRotation()
			{
				return m_Rotation;
			}
		private:

			std::wstring m_Path;


			size_t m_CurrFrameIndex = 0;
			size_t m_PrevFrameIndex;

			// 시간 변수타입이 바뀌면 변경 필요
			double m_Progress = 0;
			float m_Speed = 1.0f;

			D2D1_RECT_F m_DestRect;
			D2D1_RECT_F m_EffectRect;

			D2D1_RECT_F m_SrcRect;

			float m_ScaleX = 1.f;
			float m_ScaleY = 1.f;			
			float m_ScaleZ = 1.f;			

			Vector3 m_Scale = {1,1,1};
			float m_Rotation = 0;
		public:
			Hide::Component::AnimationAsset* m_AnimationAsset;
			std::wstring m_AnimationName;
		};
	}
}


