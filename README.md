# InLoopPeriodicCallback

Class to periodic callbacks from within the loop() function.

This library defines a class which is to be used in the loop() function of your Arduino like project which periodically calls a function of your choosing.

Because there are many ways to accomplish this simple and frequently function, you
may be wondering why this library is useful. The reason is this.

This class provides a synchronous periodic callback to a function. Often in Microcontroller programming a function needs to be called periodically, for example to sample a sensor, take an action, or write results. Particle, and other MCU environments, provide Software Timers, however they are fired from separate threads and so take on additional complication of being asynchronous from the normal loop() cycle. Another option is to simply use delay() in loop(), but that becomes complicated if there is the desire to have more than one periodic cycle going at a time. Also, the exact timing can get thrown off if the functions themselves take a variable amount of time, like writing to the internet does.

This class takes care of that and simplifies the exact timing of the callbacks.

## Usage

Connect Particle hardware, add the InLoopPeriodicCallback library to your project and follow this simple example: ExampleInLoopPeriodicCallback.ino

## LICENSE

See LICENSE
