#include "combatPlayer.h"

CombatPlayer::CombatPlayer(int hitPoints, int manaPoints, int armor) : Combat(hitPoints, manaPoints, armor)
, m_isAttackPressed(false), m_isAttackPressedPrevState(false)
{
}

bool CombatPlayer::IsAttack() const
{
	if (m_isAttackPressed)
	{
		if (!m_isAttackPressedPrevState)
		{
			return true;
		}
	}
	return false;
}
