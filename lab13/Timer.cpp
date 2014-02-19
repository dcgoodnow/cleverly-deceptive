/**
  * @file Timer.cpp
  * @author Daniel Goodnow
*/
#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"


/**
 * @name Constructor
 * 
 * @brief Creates a timer object and initializes the wasStarted parameter to 
 * false.
 *
 * @pre Timer object is not instantiated
 * @post Timer is initialized
*/
Timer::Timer() {
	timerWasStarted = false;
}

/**
 *	@name start
 *	
 *	@brief Starts the timer.
 *
 *	@pre Timer is not started
 *	@post Timer is started and the start time is stored in beginTime.
*/
void Timer::start()
{
	if(!timerWasStarted)
	{
		timerWasStarted = true;
		gettimeofday(&beginTime, NULL);
	}
}

/**
 *	@name stop
 *
 *	@brief Stops the timer and calculates the duration.
 *	@algorithm Stores the stopping time and converts this to a double by adding
 *	the microseconds to the seconds component of the timeval struct. The 
 *	beginning time is then converted in the same way and subtracted from the end
 *	value. The result is stored in the duration data member.
 *
 *	@pre Timer has been started
 *	@post Timer is stopped, duration is stored in the duration data member.
*/
void Timer::stop()
{
	if(timerWasStarted)
	{
		timeval endTime;
		gettimeofday(&endTime, NULL);
		duration = endTime.tv_usec + endTime.tv_sec * 1000000;
		duration -= beginTime.tv_usec + beginTime.tv_sec * 1000000;
		duration /= 1000000;
		timerWasStarted = false;
	}
}

/**
 * @name getElapsedTime
 *
 * @brief Returns elapsed time of the timer.
 *
 * @pre Timer is stopped
 *
 * @return Duration timer was running.
*/
double Timer::getElapsedTime() const
{
	if(!timerWasStarted)
	{
		return duration;
	}
	else
	{
		return 0.0;
	}
}

#endif
