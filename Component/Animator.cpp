#include "pch.h"
#include "Animator.h"

void Engine::Component::Animator::SetState(std::wstring _state)
{
	m_CurrFrameIndex = 0;
	m_AnimationName = _state;
	m_Progress = 0;
}

void Engine::Component::Animator::SetResourcePath(std::wstring _path)
{
	m_Path = _path;
}

void Engine::Component::Animator::Play(ULONGLONG _time)
{
	Hide::Component::FrameInfo frame;
	size_t maxFrameCount = m_AnimationAsset->animations[m_AnimationName].frameInfo.size();
	if (maxFrameCount == 0)
	{
		return;
	}
	/*else if (m_CurrFrameIndex >= maxFrameCount)
	{
		m_CurrFrameIndex = 0;
		
	}*/
	if (m_AnimationAsset->animations.find(m_AnimationName) != m_AnimationAsset->animations.end())
	{
		frame = m_AnimationAsset->animations[m_AnimationName].frameInfo[m_CurrFrameIndex];
	}
	else
	{
		frame = m_AnimationAsset->animations[m_DefaultAnimName].frameInfo[m_CurrFrameIndex];
	}

	

	m_Progress += (double)_time / 1000.0 * m_Speed;
	m_PrevFrameIndex = m_CurrFrameIndex;

	if (m_Progress > frame.time)
	{
		m_Progress = 0;
		if (m_AnimationAsset->animations[m_AnimationName].m_bLoop == true)
		{
			m_CurrFrameIndex = (m_CurrFrameIndex + 1) % maxFrameCount;
		}
		else
		{
			m_CurrFrameIndex = min(m_CurrFrameIndex + 1, maxFrameCount - 1);
		}
	}

	// 마지막 프레임으로 번호가 변할때 단한번 이벤트 호출
	if (m_CurrFrameIndex != m_PrevFrameIndex && m_CurrFrameIndex == (maxFrameCount - 1))
	{
		if (m_AnimationName.find(L"Attack") != std::wstring::npos)
		{
			m_bIsAnimationEnd = true;
		}
		//GetEntity()->OnAnimationEnd(this, m_Name);
	}

	// 이지미에서의 프레임 영역
	m_SrcRect = frame.m_rect;
	// 그릴 영역을 0,0,with,height으로 설정하고 실제 위치는 Transform으로 설정
	m_DestRect = { 0 + m_OffsetX,0 + m_OffsetY,m_SrcRect.right - m_SrcRect.left + m_OffsetX,m_SrcRect.bottom - m_SrcRect.top + m_OffsetY };
}

ID2D1Bitmap* Engine::Component::Animator::GetBitmap()
{
	return m_AnimationAsset->pBitmap;
}
