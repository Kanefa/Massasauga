#ifndef BANDIT_H
#define BANDIT_H

#include "enemy.h"

class Bandit : public Enemy
{
public:
	Bandit(int x, int y);
	void DoWork();

private:
	Bandit(const Bandit &); // disallow copy constructor
	Bandit & operator=(const Bandit &); // disallow assignment operator
	void Combat();
	void Animate();
};
#endif
