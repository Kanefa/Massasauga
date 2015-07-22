#include "screen.h"

Screen* Screen::pInstance_ = 0;

Screen* Screen::Instance()
{
      if (!pInstance_)
         pInstance_ = new Screen;
      return pInstance_;
}

Screen::Screen() : m_screenWidth(960), m_screenHeight(640), m_screenBPP(32), m_screen(NULL)
{
}
