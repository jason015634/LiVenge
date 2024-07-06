#include "LogicAnimation.h"
#include "../System/D2DRenderer.h"

#include <cmath>
#include <wincodec.h>

void LogicAnimation::Start()
{
}

void LogicAnimation::Update()
{
	
}

void LogicAnimation::LateUpdate()
{
	if (GetEntity()->GetComponent<BattleInfo>()->IsStop() == false)
	{
		//if (m_pTool->m_Input.IsKeyTap(KEY::Y)) m_bAnimState = true;
		//if (m_pTool->m_Input.IsKeyTap(KEY::R)) m_bAnimState = false;
		//if(m_bAnimState)
		//{ 
		//	m_AnimationName = L"Idle";
		//}
		//else
		//{
		//	m_AnimationName = L"Attack";
		//}

		m_AnimationName = GetEntity()->GetComponent<BattleInfo>()->GetAnimName();
		GetEntity()->GetComponent<Engine::Component::Animator>()->SetState(m_AnimationName);


		if (m_pTool->m_Input.IsKeyTap(KEY::Z) || GetEntity()->GetComponent<BattleInfo>()->GetState() == State::Idle)
			StateUpdate(AnimState::Idle);

		if (m_pTool->m_Input.IsKeyTap(KEY::X) || GetEntity()->GetComponent<BattleInfo>()->GetState() == State::Move)
			StateUpdate(AnimState::Move);

		if (m_pTool->m_Input.IsKeyTap(KEY::C) || GetEntity()->GetComponent<BattleInfo>()->IsDamaged())
			StateUpdate(AnimState::Damaged);

		if (m_pTool->m_Input.IsKeyTap(KEY::V) || GetEntity()->GetComponent<BattleInfo>()->IsDead())
			StateUpdate(AnimState::Die);

		if (m_pTool->m_Input.IsKeyTap(KEY::Q))
			GetEntity()->GetComponent<BattleInfo>()->SetDamaged(true);


		if (m_pTool->m_Input.IsKeyTap(KEY::W))
			GetEntity()->GetComponent<BattleInfo>()->SetDirection(Dir::UP);

		if (m_pTool->m_Input.IsKeyTap(KEY::A))
			GetEntity()->GetComponent<BattleInfo>()->SetDirection(Dir::LEFT);

		if (m_pTool->m_Input.IsKeyTap(KEY::S))
			GetEntity()->GetComponent<BattleInfo>()->SetDirection(Dir::DOWN);

		if (m_pTool->m_Input.IsKeyTap(KEY::D))
			GetEntity()->GetComponent<BattleInfo>()->SetDirection(Dir::RIGHT);

		if (m_pTool->m_Input.IsKeyTap(KEY::T))
		{
			GetEntity()->GetComponent<Engine::Component::EffectAnimator>()->PlayEffect();
			GetEntity()->GetComponent<Engine::Component::EffectAnimator>()->SetOffset(-60, -150);
			GetEntity()->GetComponent<Engine::Component::EffectAnimator>()->SetScale(3, 3, 1);
		}

		///	Idle
		IdleAnimUpdate(0.9f, 0.25f);
		///	Move
		MoveAnimUpdate(0.85f, 0.85f, 0.6f, 0.75f);
		///	Damaged
		DamagedAnimUpdate();
		///	Die
		DieAnimUpdate();
	}
}

void LogicAnimation::IdleAnimUpdate(float _percentY, float _speed)
{
	if (m_stateArr[static_cast<int>(AnimState::Idle)] == true)
	{
		if (m_stateArr[static_cast<int>(AnimState::Damaged)] == true)
			return;

		_speed *= 0.001f;

		m_scaleX = m_scaleX > 1.f ? 1 : (m_scaleX += _speed);

		if (m_cosNumY <= _percentY)
			m_isIncreaseScaleY = true;
		else if (m_cosNumY >= 1.0f)
			m_isIncreaseScaleY = false;

		if (m_isIncreaseScaleY)
			m_cosNumY += _speed * m_pTool->m_Time.GetDeltaTime();
		else
			m_cosNumY -= _speed * m_pTool->m_Time.GetDeltaTime();

		m_scaleY = _percentY + (1 - _percentY) * (std::cos(m_cosNumY * 6.28319f));

		GetEntity()->GetComponent<Engine::Component::Transform>()->SetScale(m_scaleX, m_scaleY, 1);
	}
}

void LogicAnimation::MoveAnimUpdate(float _percentX, float _percentY, float _speedX, float _speedY)
{
	if (m_stateArr[static_cast<int>(AnimState::Move)] == true)
	{
		if (m_stateArr[static_cast<int>(AnimState::Damaged)] == true)
			return;

		_speedY *= 0.001f;
		_speedX *= 0.001f;

		// Y
		if (m_cosNumY <= _percentY)	m_isIncreaseScaleY = true;
		else if (m_cosNumY >= 1.0f)	m_isIncreaseScaleY = false;

		if (m_isIncreaseScaleY)
			m_cosNumY += _speedY * m_pTool->m_Time.GetDeltaTime();
		else
			m_cosNumY -= _speedY * m_pTool->m_Time.GetDeltaTime();

		m_scaleY = _percentY + (1 - _percentY) * (std::cos(m_cosNumY * 6.28319f));

		// X
		if (m_cosNumX <= _percentX)	m_isIncreaseScaleX = true;
		else if (m_cosNumX >= 1.0f)	m_isIncreaseScaleX = false;

		if (m_isIncreaseScaleX)
			m_cosNumX += _speedX * m_pTool->m_Time.GetDeltaTime();
		else
			m_cosNumX -= _speedX * m_pTool->m_Time.GetDeltaTime();

		m_scaleX = _percentX + (1 - _percentX) * (std::cos(m_cosNumX * 6.28319f));

		GetEntity()->GetComponent<Engine::Component::Transform>()->SetScale(m_scaleX, m_scaleY, 1);
	}
}

void LogicAnimation::DamagedAnimUpdate()
{
	// 이미지 픽셀 데이터 얻기
	if (m_pAnimBitmap == nullptr)
		m_pAnimBitmap = GetEntity()->GetComponent<Engine::Component::Animator>()->GetBitmap();

	if (m_pDamagedAnimBitmap == nullptr)
		MakeDamagedBitmap();

	if (m_stateArr[static_cast<int>(AnimState::Damaged)] == true)
	{
		float _speedX = 2.0f;
		float _speedY = 0.85f;
		float _percentX = 0.8f;
		float _percentY = 0.88f;

		_speedY *= 0.001f;
		_speedX *= 0.001f;

		// Y
		if (m_cosNumY <= _percentY)	m_isIncreaseScaleY = true;
		else if (m_cosNumY >= 1.0f)	m_isIncreaseScaleY = false;

		if (m_isIncreaseScaleY)
			m_cosNumY += _speedY * m_pTool->m_Time.GetDeltaTime();
		else
			m_cosNumY -= _speedY * m_pTool->m_Time.GetDeltaTime();

		m_scaleY = _percentY + (1 - _percentY) * (std::cos(m_cosNumY * 6.28319f));

		// X
		if (m_cosNumX <= _percentX)	m_isIncreaseScaleX = true;
		else if (m_cosNumX >= 1.0f)	m_isIncreaseScaleX = false;

		if (m_isIncreaseScaleX)
			m_cosNumX += _speedX * m_pTool->m_Time.GetDeltaTime();
		else
			m_cosNumX -= _speedX * m_pTool->m_Time.GetDeltaTime();

		m_scaleX = _percentX + (1 - _percentY) * (std::cos(m_cosNumX * 6.28319f));

		GetEntity()->GetComponent<Engine::Component::Transform>()->SetScale(m_scaleX, m_scaleY, 1);


		// 흰색예제
		GetEntity()->GetComponent<Engine::Component::Animator>()->SetBitmap(m_pDamagedAnimBitmap);

		m_isWhite = true;

		m_Damagedtime += m_pTool->m_Time.GetDeltaTime();
		if (m_Damagedtime > 200)
		{
			m_Damagedtime = 0;

			// 흰색 예제
			GetEntity()->GetComponent<Engine::Component::Animator>()->SetBitmap(m_pAnimBitmap);
		
			m_isWhite = false;
			m_stateArr[static_cast<int>(AnimState::Damaged)] = false;
			
			m_scaleX = 1;
			m_scaleY = 1;
			GetEntity()->GetComponent<Engine::Component::Transform>()->SetScale(1, 1, 1);

			GetEntity()->GetComponent<BattleInfo>()->SetDamaged(false);
		}
	}
	else if (m_stateArr[static_cast<int>(AnimState::Damaged)] == false)
	{
		if (m_pAnimBitmap != nullptr)
		{
			if (true == m_isWhite)
			{
				m_Damagedtime += m_pTool->m_Time.GetDeltaTime();
				if (m_Damagedtime > 200)
				{
					m_Damagedtime = 0;

					// 흰색 예제
					GetEntity()->GetComponent<Engine::Component::Animator>()->SetBitmap(m_pAnimBitmap);
					
					m_scaleX = 1;
					m_scaleY = 1;
					GetEntity()->GetComponent<Engine::Component::Transform>()->SetScale(1, 1, 1);
					m_isWhite = false;
					GetEntity()->GetComponent<BattleInfo>()->SetDamaged(false);
				}
			}
			// 흰색 예제
		//	GetEntity()->GetComponent<Engine::Component::Render>()->SetBitmap(m_pAnimBitmap);
		//	m_Damagedtime = 0;
		}
	}
}

void LogicAnimation::DieAnimUpdate()
{
	if (m_stateArr[static_cast<int>(AnimState::Die)] == true)
	{
		m_alpha -= 0.005f;
		if (m_alpha <= 0) m_alpha = 0;
		GetEntity()->GetComponent<Engine::Component::Animator>()->SetAlpha(m_alpha);
		if (m_alpha == 0)
		{
			GetEntity()->GetComponent<BattleInfo>()->SetDeadComplate();
		}
	}
}

void LogicAnimation::Finalize()
{
	if (m_pDamagedAnimBitmap != nullptr)
	{
		m_pDamagedAnimBitmap->Release();
	}
}

void LogicAnimation::MakeDamagedBitmap()
{
	// 이미지 로드
	IWICBitmapDecoder* pDecoder = nullptr;

	std::wstring now_bitPath = GetEntity()->GetComponent<Engine::Component::Animator>()->GetPath();

	Engine::System::D2DRenderer::GetImageFactory()->CreateDecoderFromFilename(now_bitPath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

	IWICBitmapFrameDecode* pFrame = nullptr;
	pDecoder->GetFrame(0, &pFrame);

	// 이미지 크기 정보 가져오기
	UINT32 width, height;
	pFrame->GetSize(&width, &height);

	// 픽셀 데이터를 저장할 배열 생성
	UINT32* pixels = new UINT32[width * height];

	// 픽셀 데이터 가져오기
	pFrame->CopyPixels(nullptr, width * sizeof(UINT32), width * height * sizeof(UINT32), reinterpret_cast<BYTE*>(pixels));

	for (UINT32 y = 0; y < height; y++)
	{
		for (UINT32 x = 0; x < width; x++)
		{
			UINT32 pixel = pixels[y * width + x];
			UINT8 alpha = static_cast<UINT8>((pixel >> 24) & 0xFF);

			// 불투명한 경우 흰색 픽셀로 설정
			if (alpha > 0)
				pixels[y * width + x] = 0xFFFFFFFF; // 흰색 RGBA 값			
			else
				pixels[y * width + x] = 0; // 투명 RGBA 값
		}
	}

	// 1. 수정된 픽셀 데이터를 ID2D1Bitmap으로 변환

	D2D1_BITMAP_PROPERTIES bitmapProperties = D2D1::BitmapProperties(
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	HRESULT hr = Engine::System::D2DRenderer::GetRenderTarget()->CreateBitmap(
		D2D1::SizeU(width, height),
		pixels, // 수정된 픽셀 데이터
		width * sizeof(UINT32),
		bitmapProperties,
		&m_pDamagedAnimBitmap
	);

	delete[] pixels;
	if (pFrame) {
		pFrame->Release();
	}
	if (pDecoder) {
		pDecoder->Release();
	}
}

void LogicAnimation::SetAnimName(std::wstring _animName)
{
	m_AnimationName = _animName;
}

void LogicAnimation::StateUpdate(AnimState _state)
{
	// 다른 상태일때, 데미지를 받으면 그 상태 그대로 하얀색 이미지.
	if (_state == AnimState::Damaged)
	{
		m_stateArr[static_cast<int>(AnimState::Damaged)] = true;
		return;
	}

	for (int i = 0; i < static_cast<int>(AnimState::Max); i++)
	{
		if (i == static_cast<int>(_state))
		{
			m_stateArr[i] = true;
			continue;
		}
		m_stateArr[i] = false;
	}
}
