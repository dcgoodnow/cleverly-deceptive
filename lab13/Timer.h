/**
 * @file Timer.h
 * @author Daniel Goodnow
 *
 * @mainpage Simple Timer
 * @detail This is a simple function timer that can be used to time operations
 * performed by a program. It has 3 primary functions: start, stop, and
 * getElapsedTime, which function as they are named. 
*/

#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <iostream>

using namespace std;


class Timer {
  public:
    Timer();
    void start();
    void stop();
    double getElapsedTime() const;

  private:
    timeval beginTime;
    double duration;
    bool timerWasStarted;
};

#endif	// ifndef TIMER_H
