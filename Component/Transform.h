#pragma once
#include "Component.h"

#include <d2d1.h>
namespace Engine
{
	namespace Component
	{
		class Transform : public Component
		{
		public:
			Transform() {};
			~Transform() {};
		
			// 필수 구현부
		public:

			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Transform;

			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			// --------------필수 구현부---------------------

		public:

			const D2D1_MATRIX_3X2_F& GetLocalTransform();

			void SetLocalTransform();

			const D2D1_MATRIX_3X2_F& GetWorldTransform();

			void SetWorldTransform(D2D1_MATRIX_3X2_F _parent = D2D1::Matrix3x2F::Identity());

			const void SetScrrenTransform(D2D1_MATRIX_3X2_F _camera);

			const D2D1_MATRIX_3X2_F& GetScrrenTransform();

			void SetPosition(FLOAT _x, FLOAT _y, FLOAT _z = 0)
			{ 
				m_Position.X = _x;
				m_Position.Y = _y;
				m_Position.Z = _z;
			};
			void AddPosition(FLOAT _x, FLOAT _y, FLOAT _z = 0)
			{
				m_Position.X += _x;
				m_Position.Y += _y;
				m_Position.Z += _z;
			};

			void SetScale(FLOAT _x, FLOAT _y, FLOAT _z = 1)
			{
				m_Scale.X = _x;
				m_Scale.Y = _y;
				m_Scale.Z = _z;
			}

			void SetRotation(FLOAT _x, FLOAT _y, FLOAT _z)
			{
				m_Rotation.X = _x;
				m_Rotation.Y = _y;
				m_Rotation.Z = _z;
			}

			void SetScaleOrigin(FLOAT _x, FLOAT _y)
			{
				m_ScaleOrigin = { _x,_y };
			}

		public:
			Vector3 m_Position = {0,0,0};
			Vector3 m_Rotation = {0,0,0};
			Vector3 m_Scale = {1,1,1};

		private:
			D2D1_MATRIX_3X2_F m_LocalTransform;		// 로컬좌표
			D2D1_MATRIX_3X2_F m_WorldTransform;		// 월드좌표
			D2D1_MATRIX_3X2_F m_ScreenTransform;	// 월드좌표 * 카메라 역행렬
			D2D1_POINT_2F m_ScaleOrigin = {0,0};

		};
	}
}


