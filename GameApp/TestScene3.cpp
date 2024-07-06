#include "TestScene3.h"
#include "../Component/ComponentList.h"

#include "TestUnit.h"
#include "DataManager.h"
#include "SoundMgr.h"
#include "Player.h"

#include <vector>

void TestScene3::Initialize()
{
	m_pPlayer = new Player();
	AddEntity(m_pPlayer);
	AddEntity(&m_Camera);
	m_Camera.GetComponent<Engine::Component::Transform>()->SetPosition(-285, 0, 0);
	m_tileManager.Initialize();

	for (size_t y = 0; y < m_tileManager.GetTileMap().size(); y++)
	{
		for (size_t x = 0; x < m_tileManager.GetTileMap()[y].size(); x++)
		{
			AddEntity(m_tileManager.GetTileMap()[y][x].GetTile());
			GetHierarchyEntity()->back()->GetComponent<Engine::Component::Transform>()->SetPosition((x * 150), (y * 150), 0);
		}
	}

	// 이거로 벡터 사용
	m_tileManager.GetTileMap();
	//m_pPlayer = new TestUnit();
	m_pPlayer->AddComponent<Engine::Component::EffectAnimator>();
	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->SetOffset(0, 0);
	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->SetScale(3, 3, 1);
	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->SetResourcePath(DataManager::GetInstance().m_EffectDatas[0].m_Path);

	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Arrow_Tower");


	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->m_AnimationAsset = &DataManager::GetInstance().m_EffectDatas[0];

	m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->SetLayer(100);


	//AddEntity(m_pPlayer);


	m_Effect = new Engine::Entity::Entity();
	m_Effect->AddComponent<Engine::Component::Render>();
	m_Effect->AddComponent<Engine::Component::Transform>()->SetPosition(500, 500, 0);	
	m_Effect->AddComponent<Engine::Component::Transform>()->SetScale(1, 1, 1);
	m_Effect->AddComponent<Engine::Component::Animator>()->SetResourcePath(DataManager::GetInstance().m_EffectDatas[0].m_Path);

	m_Effect->GetComponent<Engine::Component::Animator>()->SetState(L"Arrow_Tower");
	m_Effect->GetComponent<Engine::Component::Animator>()->m_AnimationAsset = &DataManager::GetInstance().m_EffectDatas[0];
	m_Effect->GetComponent<Engine::Component::Animator>()->SetLayer(4);
	AddEntity(m_Effect);


//	m_pSound = new SoundMgr;
	SoundMgr::Instance().Initialize("../../../3_Media/BGM/");
	SoundMgr::Instance().Initialize("../../../3_Media/SFX/");
}

void TestScene3::Finalize()
{
}

void TestScene3::Start()
{
	//m_mySound->Play(CHANNEL::BGM, "../../../3_Media/BGM/(loop)After the battle _.ogg");
	//m_mySound->SetVolume(CHANNEL::BGM, 0.3f);
}

void TestScene3::FixedUpdate()
{
}

void TestScene3::Update()
{
	if (m_pTool->m_Input.IsKeyTap(KEY::P))
	{
		Engine::Scene::ChangeScene(L"TestScene");
	}

	SoundMgr::Instance().Update();

	for (size_t y = 0; y < m_tileManager.GetTileMap().size(); y++)
	{
		for (size_t x = 0; x < m_tileManager.GetTileMap()[y].size(); x++)
		{
			if (m_tileManager.GetTileMap()[y][x].GetTile()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
			{
				m_tileManager.GetTileMap()[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Green));	

				// Test Attack Range
				FindAttackRange(x, y, NULL);
			}
			else
			{
				m_tileManager.GetTileMap()[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Aqua));
			}
		}
	}

	for (auto& [x,y] : m_coordinateVec)
	{
		if (x < 0 || y < 0 || y >= m_tileManager.GetTileMap().size() || x >= m_tileManager.GetTileMap()[y].size())
			continue;

		m_tileManager.GetTileMap()[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	}

	if (m_pTool->m_Input.IsKeyTap(KEY::Q))
	{
		m_pPlayer->GetComponent<Engine::Component::EffectAnimator>()->PlayEffect();
		SoundMgr::Instance().Play(CHANNEL::BGM, "../../../3_Media/BGM/(loop)After the battle _.ogg");
	}

	if (m_pTool->m_Input.IsKeyTap(KEY::W))
		SoundMgr::Instance().Play(SFX, "../../../3_Media/SFX/Voice.mp3");

	if (m_pTool->m_Input.IsKeyTap(KEY::E))
		SoundMgr::Instance().Play(SFX, "../../../3_Media/SFX/Wind.mp3");
}

void TestScene3::LateUpdate()
{
}

AttackType TestScene3::FindAttackType(int _id)
{
	if (_id == 11 || _id == 22)
	{
		return AttackType::ShortRangeAttack;
	}
	else if (_id == 33 || _id == 44)
	{
		return AttackType::LongRangeAttack;
	}
	else if (_id == 55 || _id == 66)
	{
		return AttackType::Projectile;
	}
	else if (_id == 77 || _id == 88)
	{
		return AttackType::Projectile;
	}
	else if (_id == 99 || _id == 100)
	{
		return AttackType::Summons;
	}
	else if (_id == 1 || _id == 2)
	{
		return AttackType::Line;
	}
	else
	{
		return AttackType::None;
	}
}

void TestScene3::FindAttackRange(int _x, int _y, int _id)
{
	switch (FindAttackType(_id))
	{
	case AttackType::ShortRangeAttack:
		m_coordinateVec = ShortRange(_x, _y);
		break;
	case AttackType::LongRangeAttack:
		m_coordinateVec = LongRange(_x, _y);
		break;
	case AttackType::Drain:
		m_coordinateVec = DrainRange(_x, _y);
		break;
	case AttackType::Projectile:
		m_coordinateVec = ProjectileRange(_x, _y);
		break;
	case AttackType::Summons:
		m_coordinateVec = SummonsRange(_x, _y);
		break;
	case AttackType::Line:
		m_coordinateVec = LineRange(_x, _y);
		break;

	default:		
		m_coordinateVec = {};
		break;
	}
};

std::vector<std::pair<int, int>> TestScene3::RotatePoints(const std::vector<std::pair<int, int>>& _points, Dir1 _dir) 
{
	std::vector<std::pair<int, int>> rotatedPoints;

	switch (_dir)
	{
	case Dir1::Up:
		break;
	case Dir1::Down:
		for (const auto& point : _points) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(-x, -y)); // 180도 회전
		}
		break;
	case Dir1::Left:
		for (const auto& point : _points) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(y, -x)); // -90도 회전
		}
		break;
	case Dir1::Right:
		for (const auto& point : _points) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(-y, x)); // 90도 시계방향 회전
		}
		break;
	}

	return rotatedPoints;
}

std::vector<std::pair<int, int>> TestScene3::ShortRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec = {};

	outPutVec.push_back({ _x - 1 , _y}); // 좌
	outPutVec.push_back({ _x + 1 , _y}); // 우
	outPutVec.push_back({ _x , _y - 1}); // 상
	outPutVec.push_back({ _x , _y + 1}); // 하

	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::LongRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;

	outPutVec.push_back({ _x - 1, _y - 1 });
	outPutVec.push_back({ _x - 1, _y + 1 });
	outPutVec.push_back({ _x + 1, _y - 1 });
	outPutVec.push_back({ _x + 1, _y + 1 });

	outPutVec.push_back({ _x - 1 , _y     }); // 좌
	outPutVec.push_back({ _x + 1 , _y     }); // 우
	outPutVec.push_back({ _x     , _y - 1 }); // 상
	outPutVec.push_back({ _x     , _y + 1 }); // 하

	outPutVec.push_back({ _x - 2 , _y - 1 }); // 좌2
	outPutVec.push_back({ _x - 2 , _y + 1 });
	outPutVec.push_back({ _x - 2 , _y     });

	outPutVec.push_back({ _x + 2 , _y - 1 }); // 우2
	outPutVec.push_back({ _x + 2 , _y + 1 });
	outPutVec.push_back({ _x + 2 , _y     });

	outPutVec.push_back({ _x - 1 , _y - 2 }); // 상2
	outPutVec.push_back({ _x + 1 , _y - 2 });
	outPutVec.push_back({ _x     , _y - 2 });

	outPutVec.push_back({ _x - 1 , _y + 2 }); // 하2
	outPutVec.push_back({ _x + 1 , _y + 2 });
	outPutVec.push_back({ _x     , _y + 2 });
	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::DrainRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ _x - 1, _y     });
	outPutVec.push_back({ _x - 1, _y - 1 });
	outPutVec.push_back({ _x    , _y - 1 });
	outPutVec.push_back({ _x + 1, _y - 1 });
	outPutVec.push_back({ _x + 1, _y     });

	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::ProjectileRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;	

	for (int i = 1; i < (m_tileManager.GetTileMap().size()); i++)
	{
		outPutVec.push_back({ _x - 1, _y - i });
		outPutVec.push_back({ _x + 1, _y - i });
		outPutVec.push_back({ _x    , _y - i });
	}

	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::SummonsRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ _x - 1, _y - 1 });
	outPutVec.push_back({ _x - 1, _y + 1 });
	outPutVec.push_back({ _x + 1, _y - 1 });
	outPutVec.push_back({ _x + 1, _y + 1 });

	outPutVec.push_back({ _x - 1 , _y }); // 좌
	outPutVec.push_back({ _x + 1 , _y }); // 우
	outPutVec.push_back({ _x     , _y - 1 }); // 상
	outPutVec.push_back({ _x     , _y + 1 }); // 하

	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::LineRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;

	for (int i = 1; i < (m_tileManager.GetTileMap().size()); i++)
	{
		outPutVec.push_back({ _x    , _y - i });
	}

	return outPutVec;
}
std::vector<std::pair<int, int>> TestScene3::DebufRange(int _x, int _y)
{
	std::vector<std::pair<int, int>> outPutVec;

	outPutVec.push_back({ _x - 1, _y - 1 });
	outPutVec.push_back({ _x - 1, _y + 1 });
	outPutVec.push_back({ _x + 1, _y - 1 });
	outPutVec.push_back({ _x + 1, _y + 1 });

	outPutVec.push_back({ _x - 1 , _y }); // 좌
	outPutVec.push_back({ _x + 1 , _y }); // 우
	outPutVec.push_back({ _x     , _y - 1 }); // 상
	outPutVec.push_back({ _x     , _y + 1 }); // 하

	outPutVec.push_back({ _x - 2 , _y - 1 }); // 좌2
	outPutVec.push_back({ _x - 2 , _y + 1 });
	outPutVec.push_back({ _x - 2 , _y });

	outPutVec.push_back({ _x + 2 , _y - 1 }); // 우2
	outPutVec.push_back({ _x + 2 , _y + 1 });
	outPutVec.push_back({ _x + 2 , _y });

	outPutVec.push_back({ _x - 1 , _y - 2 }); // 상2
	outPutVec.push_back({ _x + 1 , _y - 2 });
	outPutVec.push_back({ _x     , _y - 2 });

	outPutVec.push_back({ _x - 1 , _y + 2 }); // 하2
	outPutVec.push_back({ _x + 1 , _y + 2 });
	outPutVec.push_back({ _x     , _y + 2 });

	outPutVec.push_back({ _x - 2 , _y + 2 });
	outPutVec.push_back({ _x - 2 , _y + 2 });
	outPutVec.push_back({ _x + 2 , _y - 2 });
	outPutVec.push_back({ _x + 2 , _y - 2 });

	return outPutVec;
}
