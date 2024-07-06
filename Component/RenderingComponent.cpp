#include "pch.h"
#include "RenderingComponent.h"

void Engine::Component::RenderingComponent::SetLayer(UINT _layer)
{
	if (m_MaxLayer + 1 < _layer)
	{
		m_MaxLayer = m_MaxLayer + 1;
		m_Layer = m_MaxLayer;
		return;
	}
	else
	{
		m_Layer = _layer;
		return;
	}
}

void Engine::Component::RenderingComponent::SetColor(D2D1_COLOR_F _color)
{
	m_color = _color;
}

void Engine::Component::RenderingComponent::SetColor(float* _color)
{
	m_color.r = _color[0];
	m_color.g = _color[1];
	m_color.b = _color[2];
	m_color.a = _color[3];
}
