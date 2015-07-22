#ifndef ENEMY_H
#define ENEMY_H

#include "../../Engine/matter.h"
#include "../../Engine/image.h"
#include "../Combat/combatEnemy.h"
#include "SDL.h"
#include <string>
#include <vector>

class Enemy : public Matter
{
public:
	Enemy(std::string EnemyName, int x, int y);
	virtual void Show();
	virtual void DoWork() = 0;

	Combat& GetCombat() {return m_combat;}

protected:
	std::string m_imageFile;
	int m_clipIndex;
	std::vector<SDL_Rect> m_clips; //The portions of the sprite map to be blitted
	Image m_image;
	CombatEnemy m_combat;

private:
	Enemy(const Enemy &); // disallow copy constructor
	Enemy & operator=(const Enemy &); // disallow assignment operator
	virtual void Combat() = 0;
	virtual void Animate() = 0;
	bool ReadXML();

	const std::string m_enemyName;
};
#endif