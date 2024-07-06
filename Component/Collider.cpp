#include "pch.h"
#include "Collider.h"

void Engine::Component::Collider::SetColliderInfo(float _width, float _height)
{
	m_width = _width;
	m_height = _height;
}

Engine::Component::Vector3 Engine::Component::Collider::GetOrigin()
{
	return m_origin;
}

D2D1_RECT_F Engine::Component::Collider::SetColliderRect(D2D1_MATRIX_3X2_F _x)
{
	m_origin.X = _x.dx;
	m_origin.Y = _x.dy;
	D2D1_RECT_F tempCollider
	{
		m_origin.X - m_width, m_origin.Y + m_height,m_origin.X + m_width, m_origin.Y - m_height
	};

	return tempCollider;
}

D2D1_RECT_F Engine::Component::Collider::SetColliderRect(FLOAT _x, FLOAT _y)
{
	m_origin.X = _x;
	m_origin.Y = _y;
	D2D1_RECT_F tempCollider
	{
		m_origin.X - m_width, m_origin.Y + m_height,m_origin.X + m_width, m_origin.Y - m_height
	};

	return tempCollider;
	return D2D1_RECT_F();
}
