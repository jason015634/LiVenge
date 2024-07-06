#include "pch.h"
#include "EffectAnimator.h"

void Engine::Component::EffectAnimator::Play(ULONGLONG _time)
{
	if (m_AnimationName.empty())
	{
		return;
	}
	Hide::Component::FrameInfo frame = m_AnimationAsset->animations[m_AnimationName].frameInfo[m_CurrFrameIndex];;

	size_t maxFrameCount = m_AnimationAsset->animations[m_AnimationName].frameInfo.size();

	m_Progress += (double)_time / 10000.0 * m_Speed;
	m_PrevFrameIndex = m_CurrFrameIndex;

	while (m_Progress > frame.time)
	{
		m_Progress -= frame.time;
		if (m_AnimationAsset->animations[m_AnimationName].m_bLoop == true)
		{
			m_CurrFrameIndex = (m_CurrFrameIndex + 1) % maxFrameCount;
		}
		else
		{
			m_CurrFrameIndex = min(m_CurrFrameIndex + 1, maxFrameCount - 1);
		}
	}

	// ������ ���������� ��ȣ�� ���Ҷ� ���ѹ� �̺�Ʈ ȣ��
	if (m_CurrFrameIndex != m_PrevFrameIndex && m_CurrFrameIndex == (maxFrameCount - 1))
	{
		SetActive(false);
	}

	// �����̿����� ������ ����
	m_SrcRect = frame.m_rect;
	// �׸� ������ 0,0,with,height���� �����ϰ� ���� ��ġ�� Transform���� ����
	m_DestRect = { 0 + m_OffsetX,0 + m_OffsetY,m_SrcRect.right - m_SrcRect.left + m_OffsetX,m_SrcRect.bottom - m_SrcRect.top + m_OffsetY };
}
