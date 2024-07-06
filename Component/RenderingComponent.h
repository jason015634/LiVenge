#pragma once
#include "Component.h"
#include <d2d1.h>

namespace Engine
{
	namespace Component
	{
		class RenderingComponent : public Component
		{
		public:
			RenderingComponent() {}
			virtual ~RenderingComponent() {}
		public:
			UINT GetLayer() { return m_Layer; }
			void SetLayer(UINT _layer);

			const static UINT GetMaxLayer() { return m_MaxLayer; }

			float GetAlpha() { return m_Alpha; }
			void SetAlpha(float _alpha) { m_Alpha = _alpha; };
			void ReSetAlpha() { m_Alpha = 1.0f;
			}
			const D2D1_COLOR_F& GetColor() { return m_color; }
			void SetColor(D2D1_COLOR_F _color);
			void SetColor(float* _color);

			virtual ID2D1Bitmap* GetBitmap() { return nullptr; }
			virtual void SetBitmap(ID2D1Bitmap* _bitmap) {}

			virtual void SetOffset(float _x, float _y) final
			{
				m_OffsetX = _x;
				m_OffsetY = _y;
			}

			float GetOffsetX() { return m_OffsetX; }
			float GetOffsetY() { return m_OffsetY; }

		private:
			UINT m_Layer = 0;
			static UINT m_MaxLayer;

			D2D1_COLOR_F m_color;
			float m_Alpha = 1;

		public:
			float m_OffsetX = 0;
			float m_OffsetY = 0;
		};
	}
}


