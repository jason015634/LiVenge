#include "BattleInfo.h"
#include "Entity.h"

void BattleInfo::SetChaseDistance()
{
    if (m_pChaseTarget == nullptr)
    {
        m_ChaseDistance.Reset();
		m_MoveDirection.Reset();
        return;
    }

    Position fs = m_pChaseTarget->GetComponent<BattleInfo>()->GetFieldPosition();
	fs = fs - m_FieldPosition;
    
    m_ChaseDistance.X = fs.X;
    m_ChaseDistance.Y = fs.Y;

	if (m_ChaseDistance.Y > 0)
	{
		m_MoveDirection = {0,1};
		return;
	}
	else if(m_ChaseDistance.Y < 0)
	{
		m_MoveDirection = { 0,-1 };
		return;
	}
	else if (m_ChaseDistance.X > 0)
	{
		m_MoveDirection = { -1,0 };
		return;
	}
	else if (m_ChaseDistance.X < 0)
	{
		m_MoveDirection = { 1,0 };
		return;
	}
	else
	{
		m_MoveDirection.Reset();
		return;
	}
}

std::vector<std::pair<int, int>> BattleInfo::GetAttackRange()
{
	std::vector<std::pair<int, int>> rotatedPoints;

	switch (m_Direction)
	{
	case Dir::UP:
		for (const auto& point : m_AttackRange) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(x, y));
		}
		break;
	case Dir::DOWN:
		for (const auto& point : m_AttackRange) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(-x, -y)); // 180도 회전
		}
		break;
	case Dir::LEFT:
		for (const auto& point : m_AttackRange) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(y, -x)); // -90도 회전
		}
		break;
	case Dir::RIGHT:
		for (const auto& point : m_AttackRange) {
			int x = point.first;
			int y = point.second;
			rotatedPoints.push_back(std::make_pair(-y, x)); // 90도 시계방향 회전
		}
		break;
	}

	return rotatedPoints;
}

