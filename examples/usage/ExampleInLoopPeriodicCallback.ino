//
//    ExampleInLoopPeriodicCallback.cpp
//    Purpose: Example usage for InLoopPeriodicCallback library by rvnash
//
//    Author: Richard Nash
//    Version: 1.0.2
//

// This example creates two InLoopPeriodicCallback objects with different periods.
// These objects just print the time since they were last called. Observe the output
// from a device on Serial to see how the timing works of the callbacks.
// The objects "randomly" return failure so that the behavior and timing of the callbacks
// can be observed.

#include "InLoopPeriodicCallback.h"

// Forward declare the callback functions
bool fn1(unsigned long);
bool fn2(unsigned long);
bool fn3(unsigned long);

// Construct the call back objects
InLoopPeriodicCallback cb1(fn1, 1000, 10000, 5000); // 1 second, 10 seconds, 5 seconds
InLoopPeriodicCallback cb2(fn2, 0, 3000, 10000); // 0 seconds, 3 seconds, 10 seconds
InLoopPeriodicCallback cb3(fn3, 5000, 6000, 7000, true); // 5 seconds, 6 seconds, 7 seconds using Time.now for timing

// Need to record setupTime to time the first call
unsigned long setupTime;

// First callback function
int fn1Count = 0;
unsigned long fn1LastCall;
bool fn1(unsigned long now)
{
  fn1Count++;
  if (fn1Count == 1) {
    Serial.printf("fn1 initial time: %lu", now-setupTime);
  } else {
    Serial.printf("fn1 time since last: %lu", now-fn1LastCall);
  }
  fn1LastCall = now;
  if (fn1Count % 3 == 0) { // Every 3rd call return failure
    Serial.printf(" (failure)\n");
    return false;
  } else {
    Serial.printf(" (success)\n");
    return true;
  }
}

// Second callback function
int fn2Count = 0;
unsigned long fn2LastCall;
bool fn2(unsigned long now)
{
  fn2Count++;
  if (fn2Count == 1) {
    Serial.printf("fn2 initial time: %lu", now-setupTime);
  } else {
    Serial.printf("fn2 time since last: %lu", now-fn2LastCall);
  }
  fn2LastCall = now;
  if (fn2Count % 7 == 0) { // Every 7th call return failure
    Serial.printf(" (failure)\n");
    return false;
  } else {
    Serial.printf(" (success)\n");
    return true;
  }
}

// Second callback function
int fn3Count = 0;
unsigned long fn3LastCall;
bool fn3(unsigned long now)
{
  fn3Count++;
  if (fn3Count == 1) {
    Serial.printf("fn3 initial time: %lu", now-setupTime);
  } else {
    Serial.printf("fn3 time since last: %lu", now-fn3LastCall);
  }
  fn3LastCall = now;
  if (fn3Count % 11 == 0) { // Every 11th call return failure
    Serial.printf(" (failure)\n");
    return false;
  } else {
    Serial.printf(" (success)\n");
    return true;
  }
}


void setup()
{
    Serial.begin(9600);
    setupTime = millis();
    // init() on each InLoopPeriodicCallback object, sets the initial timer to now.
    cb1.init();
    cb2.init();
    cb3.init();
}

void loop()
{
  // Must call loop() on each InLoopPeriodicCallback object
  cb1.loop();
  cb2.loop();
  cb3.loop();
}
