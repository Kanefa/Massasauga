#include "combatEnemy.h"
#include "../../Engine/globals.h"

CombatEnemy::CombatEnemy(int hitPoints, int manaPoints, int armor, int attackDelay) : Combat(hitPoints, manaPoints, armor)
, m_attackDelay(attackDelay), m_delayAttackCount(0), m_combatDelayMet(true)
{
}

void CombatEnemy::DoWork()
{
	if (!m_combatDelayMet)
	{
		//Bool is used to avoid overflowing m_delayAttackCount
		m_delayAttackCount += Globals::Instance()->GetFrameRateRegulator().GetDelta();
		if (m_attackDelay <= m_delayAttackCount)
		{
			m_combatDelayMet = true;
			m_delayAttackCount = 0;
		}
	}
}

bool CombatEnemy::IsAttack(bool isCollision)
{
	if (isCollision && m_combatDelayMet)
	{
		m_combatDelayMet = false;
		return true;
	}
	else
	{
		return false;
	}
}
