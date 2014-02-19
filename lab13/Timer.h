// Timer.h

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>

using namespace std;


class Timer {
  public:
    Timer();
    void start();
    void stop();
    double getElapsedTime() const;

  private:
    time_t beginTime;
    time_t duration;
    bool timerWasStarted;
};

#endif	// ifndef TIMER_H
