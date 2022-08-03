#include "Time.h"

// Time constructors
Time::Time() {
        setHr(0);
        setMin(0);
        setSec(0);
}

Time::Time(int hr, int min, int sec) {
        setHr(hr);
        setMin(min);
        setSec(sec);
}


// Time deconstructor
Time::~Time() {}


// Time functions
int Time::getHr() {     return t_hr;    }
int Time::getMin() {    return t_min;   }
int Time::getSec() {    return t_sec;   }

void Time::setHr(int hr) {      t_hr = hr;      }
void Time::setMin(int min) {    t_min = min;    }
void Time::setSec(int sec) {    t_sec = sec;    }