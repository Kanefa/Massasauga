#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    
    //The various clock actions
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    
    //Gets the timer's time
    int GetTicks();
    
    //Checks the status of the timer
    bool IsStarted() const;
    bool IsPaused() const;    

private:
	Timer(const Timer &); // disallow copy constructor
	Timer & operator=(const Timer &); // disallow assignment operator

    int startTicks; //The clock time when the timer started
    int pausedTicks; //The ticks stored when the timer was paused
    bool paused; //The timer status
    bool started; //The timer status
};
#endif