#pragma once
#include "Component.h"

namespace Engine
{
	namespace Component
	{
		class Camera : public Component
		{
			// 필수 구현부
		public:

			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Camera;

			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			// --------------필수 구현부---------------------

		public:
			const D2D1_MATRIX_3X2_F& SetInverseViewTransform(D2D1_MATRIX_3X2_F _CameraTrans);
			const D2D1_MATRIX_3X2_F& GetViewTransform() { return m_ViewTransform; }
		private:
			D2D1_MATRIX_3X2_F m_ViewTransform;
		};
	}
}


