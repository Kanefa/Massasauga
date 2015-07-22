#include "frameRateRegulator.h"
#include "screen.h"
#include "SDL_timer.h"
#include "windows.h"
#include <sstream>

#define MILLISECONDS_IN_A_SECOND 1000

FrameRateRegulator::FrameRateRegulator(bool isCapped, bool isDisplayed, int framesPerSecond) : m_isCapped(isCapped)
, m_isDisplayed(isDisplayed), m_framesPerSecond(framesPerSecond), m_delta(0), m_fpsMessage(" "), m_fps(0), m_frameCount(0), m_timeCount(0)
{
}

void FrameRateRegulator::Update()
{
	SetDelta();
	m_frameTimer.Start();
}

void FrameRateRegulator::Start()
{
	m_frameTimer.Start();
}

void FrameRateRegulator::SetDelta()
{
	m_delta = m_frameTimer.GetTicks();
}

void FrameRateRegulator::CapFrameRate()
{
	if ( m_isCapped )
	{
		const float minFrameTime = static_cast<float>(MILLISECONDS_IN_A_SECOND / m_framesPerSecond);
		const int elapseTime = m_frameTimer.GetTicks();
		if( elapseTime < minFrameTime )
		{ 
			//Sleep the remaining frame time
			SDL_Delay( static_cast<int>(minFrameTime - elapseTime) );
		}
	}
	//End of frame.  Update counters.
	m_frameCount++;
	m_timeCount += m_frameTimer.GetTicks();
}

void FrameRateRegulator::DisplayFrameRate()
{
	if ( m_isDisplayed )
	{
		if ( UpdateFrameRate() )
		{
			//Update text string
			std::stringstream sstream;
			sstream << "FPS: " << m_fps;
			std::string str = sstream.str();
			m_fpsMessage.Update(str);
		}
		//Display m_FPS
		m_fpsMessage.Apply(0, 0);
	}
}

bool FrameRateRegulator::UpdateFrameRate()
{
	bool result = false;

	if ( m_timeCount >= MILLISECONDS_IN_A_SECOND )
	{
		m_fps = m_frameCount;
		result = true;
		//Reset counters
		m_frameCount = 0;
		m_timeCount = 0;
	}
	return result;
}