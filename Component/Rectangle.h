#pragma once
#include "RenderingComponent.h"

namespace Engine
{
	namespace Component
	{
		class Rectangle : public RenderingComponent
		{
		public:
			Rectangle() {};
			~Rectangle() {};

			// 필수 작성부

		public:
			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Rectangle;
			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			//-------------------------------

		public:
			D2D1_RECT_F GetRect(D2D1_MATRIX_3X2_F _RectTrans);
			void SetRect(float _width, float _height);
			
			
		private:
			Vector3 m_origin;
			float m_width;
			float m_height;

			
		};
	}
}
