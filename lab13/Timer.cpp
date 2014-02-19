
#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"

Timer::Timer() : beginTime(0), duration(0) {
}

void Timer::start()
{
	beginTime = time(NULL);
	timerWasStarted = true;
}

void Timer::stop()
{
    duration = time(NULL) - beginTime;
}

double Timer::getElapsedTime() const
{
	return double(duration);
}

#endif
