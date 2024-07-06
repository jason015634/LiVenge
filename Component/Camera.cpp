#include "pch.h"
#include "Camera.h"

const D2D1_MATRIX_3X2_F& Engine::Component::Camera::SetInverseViewTransform(D2D1_MATRIX_3X2_F _CameraTrans)
{
	m_ViewTransform = _CameraTrans;
	D2D1InvertMatrix(&m_ViewTransform);
	return m_ViewTransform;
}
