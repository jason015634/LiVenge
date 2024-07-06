#pragma once
#include "RenderingComponent.h"

namespace Hide
{
	namespace Component
	{
		struct FrameInfo
		{

			D2D1_RECT_F m_rect;
			float time;
			FrameInfo() {}
			FrameInfo(int _x, int _y, int _width, int _height, float _time)
			{
				m_rect.left = _x;
				m_rect.top = _y;
				m_rect.right = _width;
				m_rect.bottom = _height;
				time = _time;
			}
			FrameInfo(D2D1_RECT_F _rect, float _time)
			{
				m_rect = _rect;
				this->time = _time;
			}
		};

		struct AnimationInfo
		{
			AnimationInfo()
			{
			};
			AnimationInfo(FrameInfo _fInfo, bool _loop = true)
			{
				frameInfo.push_back(_fInfo);
				m_bLoop = _loop;
			}
			std::vector<FrameInfo> frameInfo;
			bool m_bLoop = true;
		};

		class AnimationAsset
		{
		public:

			ULONG m_Ref = 0;
		public:
			std::wstring m_Path;

			ID2D1Bitmap* pBitmap = nullptr;
			/// <summary>
			/// name, AnimationInfo
			/// </summary>
			std::map<std::wstring, AnimationInfo> animations;

			ULONG AddRef() { m_Ref++; return m_Ref; }
			ULONG Release()
			{
				m_Ref--;
				if (m_Ref <= 0)
				{
					delete this;
					return 0;
				}
				return m_Ref;
			}

		};
	}
}

namespace Engine
{
	namespace Component
	{
		class Animator : public RenderingComponent
		{
		public:
			Animator() {}
			~Animator() {}

			// 필수 작성부
		public:
			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Animator;
			static const ULONGLONG ComponentFlag = 1 << ComponentType;
			//-------------------------------
		
		public:
			void SetState(std::wstring _state);
			void SetResourcePath(std::wstring _path);
			void Play(ULONGLONG _time);
			const std::wstring& GetPath() { return m_Path; }
			const D2D1_RECT_F& GetDestRect() { return m_DestRect; }
			const D2D1_RECT_F& GetSrcRect() { return m_SrcRect; }
			const D2D1_SIZE_F GetBitmapSize()
			{
				return{ m_DestRect.right,m_DestRect.bottom };
			}
			ID2D1Bitmap* GetBitmap() override;
			void SetBitmap(ID2D1Bitmap* _bitmap) override
			{
				m_AnimationAsset->pBitmap = _bitmap;
			}
			void SetSpeed(float _speed) { m_Speed = _speed; }

		private:

			std::wstring m_Path;


			size_t m_CurrFrameIndex = 0;
			size_t m_PrevFrameIndex;

			// 시간 변수타입이 바뀌면 변경 필요
			double m_Progress = 0;
			float m_Speed = 1.0f;

			D2D1_RECT_F m_DestRect;
			D2D1_RECT_F m_SrcRect;

		public:
			std::wstring m_AnimationName = L"Attack_Down";
			std::wstring m_DefaultAnimName = L"Idle_Up";
			Hide::Component::AnimationAsset* m_AnimationAsset;
			bool m_bIsAnimationEnd = false;
		};
	}
}