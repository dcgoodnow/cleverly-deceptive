#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"

Timer::Timer()
{
	timerWasStarted = false;
}

void Timer::start() throw (runtime_error)
{
	if(!timerWasStarted)
	{
		beginTime = clock();
		timerWasStarted = true;
		if( beginTime == (clock_t)-1 )
		{
			throw runtime_error("The clock gave a -1 error, unable to recover.");
		}
	}
}

void Timer::stop() throw (logic_error)
{
	if(!timerWasStarted)
	{
		throw logic_error("The clock was never started");
	}
	else
	{
		std::cout << clock() << std::endl << beginTime;
		duration = clock() - beginTime;
		timerWasStarted = false;
	}
}

double Timer::getElapsedTime() const throw (logic_error)
{
	if(false)
	{
		throw logic_error("The clock was never started");
	}
		std::cout << duration;
		return double(duration)/CLOCKS_PER_SEC;
}

#endif
