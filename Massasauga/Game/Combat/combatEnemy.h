#ifndef COMBATENEMY_H
#define COMBATENEMY_H

#include "combat.h"

class CombatEnemy : public Combat
{
public:
	CombatEnemy(int hitPoints, int manaPoints, int armor, int delay);
	void DoWork();

	bool IsAttack(bool isCollision);
	void SetCombatDelayMet(bool combatDelayMet) {m_combatDelayMet = combatDelayMet;}

private:
	CombatEnemy(const CombatEnemy &); // disallow copy constructor
	CombatEnemy & operator=(const CombatEnemy &); // disallow assignment operator

	const int m_attackDelay;
	int m_delayAttackCount;
	bool m_combatDelayMet;
};
#endif