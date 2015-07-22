#ifndef COMBAT_H
#define COMBAT_H

#include "SDL.h"

class Combat
{
public:
	Combat(int hitPoints, int manaPoints, int armor);
	void TakeDamage(int amount);

	int GetHitPoints() const {return m_hitPoints;}
	int GetManaPoints() const {return m_manaPoints;}
	int GetArmor() const {return m_armor;}
	bool IsDead() const {return m_dead;}	

protected:
	int m_hitPoints;
	int m_manaPoints;
	int m_armor;
	bool m_dead;

private:
	Combat(const Combat &); // disallow copy constructor
	Combat & operator=(const Combat &); // disallow assignment operator
};
#endif