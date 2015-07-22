#ifndef COMBATPLAYER_H
#define COMBATPLAYER_H

#include "combat.h"

class CombatPlayer : public Combat
{
public:
	CombatPlayer(int hitPoints, int manaPoints, int armor);

	bool IsAttack() const;
	bool IsAttackPressed() const {return m_isAttackPressed;}
	void SetAttackPressed(bool isAttackPressed) {m_isAttackPressed = isAttackPressed;}
	void SetAttackPressedPrevState(bool isAttackPressedPrevState) {m_isAttackPressedPrevState = isAttackPressedPrevState;}

private:
	CombatPlayer(const CombatPlayer &); // disallow copy constructor
	CombatPlayer & operator=(const CombatPlayer &); // disallow assignment operator
	
	bool m_isAttackPressed;
	bool m_isAttackPressedPrevState;
};
#endif