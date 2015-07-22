#ifndef FRAMERATEREGULATOR_H
#define FRAMERATEREGULATOR_H

#include "timer.h"
#include "text.h"

class FrameRateRegulator
{
public:
	FrameRateRegulator(bool isCapped = true, bool isDisplayed = false, int framesPerSecond = 120);
	int GetDelta() const {return m_delta;}
	void Update(); //Belongs at beginning of frame
	void CapFrameRate(); //Belongs at end of frame
	void DisplayFrameRate();

private:
	FrameRateRegulator(const FrameRateRegulator &); // disallow copy constructor
	FrameRateRegulator & operator=(const FrameRateRegulator &); // disallow assignment operator
	void Start();
	void SetDelta(); 
	bool UpdateFrameRate();

	const bool m_isCapped;
	const bool m_isDisplayed;
	const int m_framesPerSecond;
	Timer m_frameTimer;
	int m_delta;
	Text m_fpsMessage;
	int m_fps;
	int m_frameCount;
	int m_timeCount;
};
#endif