#include "pch.h"
#include "Transform.h"

#include <cmath>
#pragma comment(lib,"d2d1.lib")


const D2D1_MATRIX_3X2_F& Engine::Component::Transform::GetLocalTransform()
{
	return m_LocalTransform;
}

void RotationFix(FLOAT& _rotation)
{
	if (_rotation < 0)
	{
		_rotation += 360;
		return;
	}
	if (_rotation > 360)
	{
		_rotation -= 360;
		return;
	}
}

void Engine::Component::Transform::SetLocalTransform()
{
	if (m_Scale.Z <= 0)
	{
		m_Scale.Z = 0.0001;
	}
	m_LocalTransform = D2D1::Matrix3x2F::Scale(m_Scale.X * m_Scale.Z * std::cosf(m_Rotation.X), m_Scale.Y * m_Scale.Z * std::cosf(m_Rotation.Y), m_ScaleOrigin) * D2D1::Matrix3x2F::Rotation(m_Rotation.Z) * D2D1::Matrix3x2F::Translation(m_Position.X, m_Position.Y);
}

const D2D1_MATRIX_3X2_F& Engine::Component::Transform::GetWorldTransform()
{
	return m_WorldTransform;
}

void Engine::Component::Transform::SetWorldTransform(D2D1_MATRIX_3X2_F _parent)
{
	m_WorldTransform = m_LocalTransform * _parent;
}

const void Engine::Component::Transform::SetScrrenTransform(D2D1_MATRIX_3X2_F _camera)
{
	m_ScreenTransform = m_WorldTransform * _camera;
}

const D2D1_MATRIX_3X2_F& Engine::Component::Transform::GetScrrenTransform()
{
	return m_ScreenTransform;
}
