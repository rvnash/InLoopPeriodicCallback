//
//    ExponentiallySmoothedValue.h
//    Purpose: InLoopPeriodicCallback library header
//
//    Author: Richard Nash
//    Version: 1.0.0

// This class provides a synchronous periodic callback to a function.
// Often in Microcontroller programming a function needs to be called
// periodically, for example to sample a sensor, take an action, or
// write results. Particle provides Software Timers, however they are
// fired from separate threads and so take on additional complication of
// being asynchronous from the normal loop() cycle. Another option is to
// simply use delay() in loop(), but that becomes complicated if there
// is the desire to have more than one periodic cycle going at a time.
// Also, the exact timing can get thrown off if the functions themselves
// take a variable amount of time, like writing to the internet does.
//
// This class takes care of all of that. It is completely synchronous, because
// it is always called from the main loop(). See the comments here and
// the example in this library to learn how to use it.

#pragma once

// Values returned by "loop()"
#define NOT_CALLED  0
#define CALL_SUCCEEDED 1
#define CALL_FAILED 2

class InLoopPeriodicCallback
{
public:
    // No default Constructor, you need to specify the periods
    InLoopPeriodicCallback() = delete;

    // Constructor
    // Parameters:
    // fn - The function to call back. The correct declaration of this function
    //      is "bool fn(unsigned long now)". fn must return true if the call
    //      is successful, and false if it is not.
    // firstCallTime - The amount of time from initialization to the first call
    //                 of fn.
    // periodTime - The normal periodic callback timing, when fn returns success.
    // retryTime - If fn() returns false, then this time will elapse until the
    //             next call of fn()
    // Note: All times used by this class are in milliseconds
    // Note: This construction also calls init(). On the Particle there can be
    //       a significant period of time between construction, and when
    //       setup() is first called. The function init() can reset this object
    //       so the first call is the specified amount of time after setup().
    InLoopPeriodicCallback(bool (*fn)(unsigned long),
                           unsigned long firstCallTime,
                           unsigned long periodTime,
                           unsigned long retryTime );

    // Starts the initial timer. The first call to fn() will occur after
    // firstCallTime milliseconds. It is not necessary to call this in
    // setup(), but then the first call will be unreliably timed.
    void init();

    // This needs to be called in loop() very frequently. If for any reason
    // loop is delayed, then the periodic call will be delayed the same.
    // Returns one of the constants at the beginning of this file.
    int loop();

    // Returns number milliseconds until the next call.
    unsigned long msUntilNextCall();

    // Returns number milliseconds since the last call.
    unsigned long msSinceLastCall();

    // Returns true if the last call to fn() was a success, otherwise false.
    bool lastCallSuccess();

private:
    bool (*fn)(unsigned long);
    unsigned long firstCallTime;
    unsigned long periodTime;
    unsigned long retryTime;
    unsigned long msLastCall;
    unsigned long msNextCall;
    bool lastCallSuccessValue;
};
