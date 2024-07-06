#pragma once
#include "Component.h"
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		enum CollisionSide
		{
			None = 0,
			Left = 1,
			Top = 2,
			Right = 3,
			Bottom = 4
		};

		class Collider : public Component
		{
			// 필수 구현부
		public:

			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Collider;

			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			// --------------필수 구현부---------------------

		public:
			void SetColliderInfo(float _width, float _height);
			Vector3 GetOrigin();
			D2D1_RECT_F GetColliderRect()
			{
				return {m_origin.X - m_width, m_origin.Y + m_height,m_origin.X + m_width, m_origin.Y - m_height};
			}
			D2D1_RECT_F SetColliderRect(D2D1_MATRIX_3X2_F _x);
			D2D1_RECT_F SetColliderRect(FLOAT _x,FLOAT _y);

			bool AABB(D2D1_RECT_F _otherCollider)
			{
				m_bColl = false;
				if (_otherCollider.left > m_origin.X + m_width || _otherCollider.right < m_origin.X - m_width ||
					_otherCollider.top < m_origin.Y - m_height || _otherCollider.bottom >m_origin.Y + m_height)
				{
					return m_bColl;
				}
				return m_bColl = true;
			}
			bool AABB(LONG _x, LONG _y)
			{
				m_bColl = false;
				if (_x > m_origin.X + m_width || _x < m_origin.X - m_width ||
					_y < m_origin.Y - m_height || _y > m_origin.Y + m_height)
				{
					return m_bColl;
				}
				return m_bColl = true;
			}
			bool MouseAABB(LONG _x, LONG _y)
			{
				m_bIsMouseColl = false;
				if (_x > m_origin.X + m_width || _x < m_origin.X - m_width ||
					_y < m_origin.Y - m_height || _y >m_origin.Y + m_height)
				{
					return m_bIsMouseColl;
				}
				return m_bIsMouseColl = true;
			}
			void SetMouseAABB(bool _set)
			{
				m_bIsMouseColl = _set;
			}

			CollisionSide ScreenScrollAABB(LONG _x, LONG _y)
			{
				m_bColl = false; 
				if (_x > m_width- m_CameraOffset || _x < m_CameraOffset || _y < m_CameraOffset || _y > m_height - m_CameraOffset)
				{
					m_bColl = true;
					if (_x > m_width - m_CameraOffset)
					{
						m_CollisionSide = Right;
					}
					if (_x < m_CameraOffset)
					{
						m_CollisionSide = Left;
					}
					if (_y < m_CameraOffset)
					{
						m_CollisionSide = Top;
					}
					if (_y > m_height - m_CameraOffset)
					{
						m_CollisionSide = Bottom;
					}
					switch (m_CollisionSide)
					{
					case 1:
						return Left;
						break;
					case 2:
						return Top;
						break;
					case 3:
						return Right;
					case 4:
						return Bottom;
					default:
						break;
					}
				}
				else
					m_bColl = false;
			}

			const bool IsCollision() { return m_bColl; }
			const bool GetMouseColl() { return m_bIsMouseColl; }
		private:
			// 필요한 정보 : 원점 좌표 (x,y), 가로 길이, 세로 길이
			Vector3 m_origin;
			float m_width;
			float m_height;

			CollisionSide m_CollisionSide;

			Vector3 m_offset = {0,0,0};

			float m_CameraOffset = 50.0f;
			bool m_bColl;
			bool m_bIsMouseColl = false;
		};
	}
}


