#include "BattleScript.h"
#include "BattleField.h"
#include "BattleSystem.h"
#include <cmath>

void BattleScript::Update()
{
    // start 함수가 안돼서 걍 임시로 만듦
    if (m_bIsStart == false)
    {
        m_AtkDelay = GetEntity()->GetComponent<UnitStatus>()->GetAttackSpeed() * 1000;
        m_MoveDelay = GetEntity()->GetComponent<UnitStatus>()->GetMoveSpeed() * 1500;
        m_battleState = State::Idle;

        // 위치 초기화
        m_myPos = GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition();
        BattleField::GetInstance().SetTakeTile(m_myPos.X, m_myPos.Y, GetEntity());

        m_bIsStart = true;
    }

    // 자신이 장애물 오브젝트
    if (GetEntity()->GetComponent<UnitStatus>()->GetUnitID() > 300)
        return;

    switch (m_battleState)
    {
    case State::Idle:
        UpdateIdle();
        UpdateAnim();
        BaseUpdate();

        DetectTarget();

        SetAttackTarget();
        SetLookDir();
        break;

    case State::Move:
        UpdateMove();
        UpdateAnim();
        BaseUpdate();
        SetLookDir();
        break;

    case State::Attack:
        UpdateAttack();
        UpdateAnim();
        BaseUpdate();
        break;

    case State::Die:
        UpdateDie();
        break;
    }

    GetEntity()->GetComponent<UnitStatus>()->EffectReset();
}

void BattleScript::DefaultAttack()
{
    // 단일 공격
    if (GetEntity()->GetComponent<UnitStatus>()->Unit_MultiAttack == false)
    {
        if (GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget().empty() == true)
        {
            m_battleState = State::Idle;
            return;
        }

        auto target = GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget().back();
        target->GetComponent<UnitStatus>()->UnitGetDamage(GetEntity()->GetComponent<UnitStatus>()->GetAttack());
        target->GetComponent<BattleInfo>()->SetDamaged(true);

        GetEntity()->GetComponent<Engine::Component::EffectAnimator>()->PlayEffect();

        // 바라보는 위치 설정하기
        m_LookPosition = GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget().back()->GetComponent<BattleInfo>()->GetFieldPosition() - GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition();
    }
    // 멀티 공격
    else
    {
        bool isAttack = false;
        for (auto target : GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget())
        {
            if (target->GetComponent<BattleInfo>()->IsDead())
                continue;

            target->GetComponent<UnitStatus>()->UnitGetDamage(GetEntity()->GetComponent<UnitStatus>()->GetAttack());
            target->GetComponent<BattleInfo>()->SetDamaged(true);

            if (GetEntity()->GetComponent<UnitStatus>()->GetUnitID() == 103)
            {
                GetEntity()->GetComponent<UnitStatus>()->HealthyDrain(10);
            }

            isAttack = true;
        }
        if (isAttack == false)
        {
            m_AttackTime += GetEntity()->GetComponent<UnitStatus>()->GetAttackSpeed();
            GetEntity()->GetComponent<BattleInfo>()->SetState(State::Idle);
            m_battleState = State::Idle;
            return;
        }
    }
}

void BattleScript::DebuffTower()
{
    for (auto target : GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget())
    {
        target->GetComponent<UnitStatus>()->SetEffectMoveSpeed(GetEntity()->GetComponent<UnitStatus>()->GetAttack());
    }
}

void BattleScript::SetLookDir()
{
    if (m_MoveDistanceX > 0)
    {
        m_lookDir = Dir::RIGHT;
        return;
    }
    else if (m_MoveDistanceX < 0)
    {
        m_lookDir = Dir::LEFT;
        return;
    }
    else if (m_MoveDistanceY > 0)
    {
        m_lookDir = Dir::DOWN;
        return;
    }
    else if (m_MoveDistanceY < 0)
    {
        m_lookDir = Dir::UP;
        return;
    }
    else
    {
        m_lookDir = Dir::DOWN;
        return;
    }
}

void BattleScript::SetAttackTarget()
{
    m_attackTargets.clear();

    auto tileRange = GetEntity()->GetComponent<BattleInfo>()->GetAttackRange();
    auto targets = BattleField::GetInstance().GetAttackRange(tileRange, GetEntity());
    targets = m_attackTargets;
}

std::vector<Engine::Entity::Entity*>& BattleScript::GetAttackTargets()
{
    return m_attackTargets;
}

/// Update State ///
////////////////////

void BattleScript::BaseUpdate()
{
    // State  Die
    if (GetEntity()->GetComponent<UnitStatus>()->IsUnitDead())
    {
        m_battleState = State::Die;
        return;
    }
}

void BattleScript::UpdateAnim()
{
    switch (m_battleState)
    {
    case State::Idle:
        m_AnimDummyName = L"Idle";
        break;

    case State::Move:
        m_AnimDummyName = L"Move";
        break;

    case State::Attack:
        m_AnimDummyName = L"Attack";
        break;

    case State::Die:
        m_AnimDummyName = L"Die";
        break;
    }

    UpdateAnimDir(m_lookDir);
}

void BattleScript::UpdateAnimDir(Dir _dir)
{
    switch (_dir)
    {
    case Dir::UP:
        m_AnimDummyName.append(L"_Up");
        break;
    case Dir::DOWN:
        m_AnimDummyName.append(L"_Down");
        break;
    case Dir::LEFT:
        m_AnimDummyName.append(L"_Left");
        break;
    case Dir::RIGHT:
        m_AnimDummyName.append(L"_Right");
        break;
    }

    GetEntity()->GetComponent<BattleInfo>()->SetAnimName(m_AnimDummyName);
}

void BattleScript::UpdateIdle()
{
    m_curAtkTime += m_pTool->m_Time.GetDeltaTime();
    m_curMoveTime += m_pTool->m_Time.GetDeltaTime();

    // 적이 있다면
    if (m_attackTargets.empty() == false)
    {
        if (m_curAtkTime >= m_AtkDelay)
        {
            m_battleState = State::Attack;
            m_curAtkTime = 0.f;
            m_curMoveTime = 0.f;
        }
    }
    // 적이 없다면
    else
    {
        if (m_curMoveTime >= m_MoveDelay)
        {
            m_battleState = State::Move;
            m_curAtkTime = 0.f;
            m_curMoveTime = 0.f;
        }
    }
}

void BattleScript::UpdateMove()
{
  
    // 이동 로직 //
    //  1. 타일매니저에서 take로 바꾸고
    //   2. 이전꺼 none
    //   3. 유닛에서도 SetFieldPosition

    // 움직이지 않는 유닛
    if (GetEntity()->GetComponent<UnitStatus>()->GetUnitID() == 204 ||
        GetEntity()->GetComponent<UnitStatus>()->GetUnitID() == 205)
        return;

    if (BattleField::GetInstance().isBattleStart == false) return;

    Position myPos = GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition();
    double x = 0, y = 0, speed;

    std::vector<std::pair<int, int>> myAround =
        BattleField::GetInstance().GetSearchAround(myPos.X, myPos.Y);

    if (myAround.size() == 0) 
    {
        m_battleState = State::Idle;
        return;
    }

    if (m_myTarget == nullptr) 
    {
        std::pair<int, int> pos = myAround.back();

        if      (pos.second < 0) { m_moveDir = Dir::UP;     y = -1; }
        else if (pos.second > 0) { m_moveDir = Dir::DOWN;   y =  1; }
        else if (pos.first < 0)  { m_moveDir = Dir::LEFT;   x = -1; }
        else if (pos.first > 0)  { m_moveDir = Dir::RIGHT;  x =  1; }
    }
    else
    {
        Position targetPos = m_myTarget->GetComponent<BattleInfo>()->GetFieldPosition();
        Position distance = targetPos - myPos;

        if (distance.Y < 0)      { m_moveDir = Dir::UP;     y = -1; }
        else if (distance.Y > 0) { m_moveDir = Dir::DOWN;   y =  1; }
        else if (distance.X < 0) { m_moveDir = Dir::LEFT;   x = -1; }
        else if (distance.X > 0) { m_moveDir = Dir::RIGHT;  x =  1; }
    }

    if (myPos.X + x >= 10 || myPos.Y + y >= 10) 
        return;


    if (BattleField::GetInstance().GetTimeManager()->GetTileInfo(myPos.X + x, myPos.Y + y).GetTileOnUnitState() != TileOnUnitState::None)
    {
        m_battleState = State::Idle;
        return;
    }

   // BattleField::GetInstance().SetMoveTile(myPos.X + x, myPos.Y + y);

    speed = GetEntity()->GetComponent<UnitStatus>()->GetMoveSpeed() + 2;

    m_MoveDistanceX += x * speed; // *m_pTool->m_Time.GetDeltaTime();
    m_MoveDistanceY += y * speed; // *m_pTool->m_Time.GetDeltaTime();

    GetEntity()->GetComponent<Engine::Component::Transform>()-> AddPosition(x * speed, y * speed);

    if (x != 0)
    {
        if (std::abs(m_MoveDistanceX) > std::abs(x * 150))
        {
            // 타일에서의 위치
            GetEntity()->GetComponent<Engine::Component::Transform>()->SetPosition
            (GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().X * 150,
                GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().Y * 150);

            BattleField::GetInstance().SetTakeTile(myPos.X + x, myPos.Y + y, GetEntity());
            BattleField::GetInstance().SetResetTile(myPos.X, myPos.Y);

            GetEntity()->GetComponent<BattleInfo>()->SetFieldPosition(myPos.X + x, myPos.Y + y);

            m_MoveDistanceX = 0;
            m_battleState = State::Idle;
        }
    }
    if (y != 0)
    {
        if (std::abs(m_MoveDistanceY) > std::abs(y * 150))
        {
            // 타일에서의 위치
            GetEntity()->GetComponent<Engine::Component::Transform>()->SetPosition
            (GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().X * 150,
                GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().Y * 150);
         
            BattleField::GetInstance().SetTakeTile(myPos.X + x, myPos.Y + y, GetEntity());
            BattleField::GetInstance().SetResetTile(myPos.X, myPos.Y);

            GetEntity()->GetComponent<BattleInfo>()->SetFieldPosition(myPos.X + x, myPos.Y + y);

            m_MoveDistanceY = 0;
            m_battleState = State::Idle;
        }
    }

    if (x + y == 0)
    {
        m_battleState = State::Idle;
    }
}

void BattleScript::DetectTarget()
{
    if (m_myTarget != nullptr) return;

    // 아군 몬스터의 타겟
    if (GetEntity()->GetComponent<UnitStatus>()->GetUnitTeamID() == 1)
    {
        Engine::Entity::Entity* target = nullptr;

        for (const auto& child : BattleField::GetInstance().m_EnemyUnit)
        {
            // Todo 좀 더 세밀한 타겟 설정
            // Todo 지금은 한마리만 타겟하게 됨.
            target = child;
        }

        m_myTarget = target;
    }

    // 적군의 타겟
    else
    {
        Engine::Entity::Entity* target = nullptr;

        for (const auto& child : BattleField::GetInstance().m_TeamUnit)
        {
            // Todo 좀 더 세밀한 타겟 설정
            // Todo 지금은 한마리만 타겟하게 됨.
            target = child;
        }
        m_myTarget = target;
    }
}

void BattleScript::UpdateAttack()
{
    // m_AttackTime += (double)(1.0 / 600.0);
    if (GetEntity()->GetComponent<BattleInfo>()->GetAttackTarget().empty())
    {
        GetEntity()->GetComponent<BattleInfo>()->SetState(State::Idle);
        return;
    }

    if (GetEntity()->GetComponent<UnitStatus>()->GetUnitID() == 205)
        DebuffTower();
    else
        DefaultAttack();
}

void BattleScript::UpdateDie()
{
    GetEntity()->GetComponent<BattleInfo>()->SetDead();
}