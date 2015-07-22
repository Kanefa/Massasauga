#include "bandit.h"
#include "../player.h"
#include "../../Engine/globals.h"

Bandit::Bandit(int x, int y) : Enemy("bandit", x, y)
{
}

void Bandit::DoWork()
{
	Combat();
	Animate();
}

void Bandit::Combat()
{
	m_combat.DoWork();

	Player& player = Globals::Instance()->getGame().getPlayer1();
	if (m_combat.IsAttack(IsCollision(player.GetRect())))
	{
		player.GetCombat().TakeDamage(20);
	}
}

void Bandit::Animate()
{
	int clipIndexPrevState = m_clipIndex;

	if (m_combat.IsDead())
	{
		m_clipIndex = 2;
	}
	else if (IsCollision(Globals::Instance()->getGame().getPlayer1().GetRect()))
	{
		m_clipIndex = 1;
	}
	else
	{
		m_clipIndex = 0;
	}
	
	if (m_clipIndex != clipIndexPrevState)
	{
		m_image = Image(m_imageFile, m_clips.at(m_clipIndex));
	}
}