#include "combat.h"

Combat::Combat(int hitPoints, int manaPoints, int armor) : m_hitPoints(hitPoints), m_manaPoints(manaPoints), m_armor(armor)
, m_dead(false)
{
}

void Combat::TakeDamage(int amount)
{
	m_hitPoints -= amount;

	if (m_hitPoints <= 0)
	{
		m_dead = true;
	}
}

