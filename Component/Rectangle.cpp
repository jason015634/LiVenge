#include "pch.h"
#include "Rectangle.h"

void Engine::Component::Rectangle::SetRect(float _width, float _height)
{
	m_width = _width;
	m_height = _height;
}

D2D1_RECT_F Engine::Component::Rectangle::GetRect(D2D1_MATRIX_3X2_F _RectTrans)
{
	m_origin.X = _RectTrans.dx;
	m_origin.Y = _RectTrans.dy;

	D2D1_RECT_F tempRect =
	{
		m_origin.X - m_width, m_origin.Y - m_height, m_origin.X + m_width, m_origin.Y + m_height
	};
	return tempRect;
}
