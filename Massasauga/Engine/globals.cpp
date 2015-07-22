#include "globals.h"
#include "keyboard.h"
#include "../Game/game.h"

Globals* Globals::pInstance_ = 0;

Globals* Globals::Instance()
{
      if (!pInstance_)
         pInstance_ = new Globals;
      return pInstance_;
}

Globals::Globals() : m_quit(false), m_frameRateRegulator(true, true, 120)
{
}
