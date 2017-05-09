//
//    ExponentiallySmoothedValue.cpp
//    Purpose: InLoopPeriodicCallback library implementation
//
//    Author: Richard Nash
//    Version: 1.0.2

// For a description of how to use this class, see the header file and example
// in this library.

#include <Particle.h>
#include "InLoopPeriodicCallback.h"

// How to determine when it is time to call fn():
// The millis() timer and the time of the next call (msNextCall) are unsigned 32 bits
// Their difference (in unsigned arithmetic) will be a large number until
// now reaches msNextCall.
// Remember, since millis() can rollover, it is possible now and msNextCall can be
// on opposite sides of the rollover point. For example now might be 0xFFFFFFFF and
// msNextCall might be 0x00000001 . It isn't time to call yet, in this example, so a
// simple (now >= msNextCall) comparison does not work.
// The window for when it is time to call is when the difference between them is "small".
// The choice of "small" is somewhat arbitrary. As millis() rolls over every 49 days,
// I'm going to pick 1 day as my "small" window.
#define CALL_DIFF_WINDOW    (unsigned long)(1000 * 60 * 60 * 24)

InLoopPeriodicCallback::InLoopPeriodicCallback(bool (*fn)(unsigned long),
                           unsigned long firstCallTime,
                           unsigned long periodTime,
                           unsigned long retryTime,
                           bool useSystemTimeInsteadofMillis )
{
    this->fn = fn;
    this->firstCallTime = firstCallTime;
    this->periodTime = periodTime;
    this->retryTime = retryTime;
    this->useSystemTimeInsteadofMillis = useSystemTimeInsteadofMillis;
    init();
}


void InLoopPeriodicCallback::init()
{
  unsigned long now = getNow();
  msLastCall = now;
  msNextCall = now + firstCallTime;
  lastCallSuccessValue = false;
}

int InLoopPeriodicCallback::loop()
{
    const unsigned long now = getNow();

    if (now - msNextCall < CALL_DIFF_WINDOW) {
        lastCallSuccessValue = fn(now);
        msLastCall = now;
        const unsigned long period = lastCallSuccessValue ? periodTime : retryTime;
        // The next call needs to be after now, so just keep adding period
        // to the next call time until we get a point in time that satisfies
        // that condition. Usually, this should be only 1 period.
        while (now - msNextCall < CALL_DIFF_WINDOW) msNextCall += period;
        return lastCallSuccessValue ? CALL_SUCCEEDED : CALL_FAILED;
    } else {
        return NOT_CALLED;
    }
}

unsigned long InLoopPeriodicCallback::msUntilNextCall()
{
    const unsigned long now = getNow();
    return msNextCall - now;
}

unsigned long InLoopPeriodicCallback::msSinceLastCall()
{
    const unsigned long now = getNow();
    return now - msLastCall;
}

bool InLoopPeriodicCallback::lastCallSuccess()
{
    return lastCallSuccessValue;
}

unsigned long InLoopPeriodicCallback::getNow()
{
    if (!useSystemTimeInsteadofMillis) {
        return millis();
    } else {
        return Time.now() * 1000UL;
    }
}

