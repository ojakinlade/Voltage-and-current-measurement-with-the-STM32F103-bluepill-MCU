#ifndef _SYSTIMER_STRUCT_H
#define _SYSTIMER_STRUCT_H

/*
Generic type for creating software timers.
Each 'sysTimer_t' struct variable can be used to
make functions or blocks of code run periodically and
without interfering with other blocks of code.

Struct members:
- start: A tick (or clock cycle) of the system timer which
marks the beginning of an operation or piece of code that is
intended to run periodically.

- ticksToWait: The time in milliseconds for which the software timer
of type 'sysTimer_t' waits. This can be used in creating delays. It also
allows the software timer to do things periodically.

- isCounting: A boolean which signifies whether a software timer of
the type 'sysTimer_t' is currently counting or not.

Usage:
To create and initialize a software timer of type 'sysTimer_t', the 
following should be done:

* sysTimer_t mySoftwareTimer; //creates software timer

	//Initializing the software timer
* mySoftwareTimer.start = 0;
* mySoftwareTimer.ticksToWait = 1500;
* mySoftwareTimer.isCounting = false;

The software timer initialization should be handled using an API for
the benefit of the main application code which should not be allowed to
modify the 'sysTimer_t' struct members directly. i.e.

* Software_Timer_Init(&mySoftwareTimer);

From the illustration above, Software_Timer_Init() is a function that initializes 
the software timer whose address is passed as an argument to the function.
Conversely, functions that require periodic execution without blocking other parts of
the main code can use a pointer to the 'sysTimer_t' software timer (i.e. sysTimer_t*) 
as a parameter so that the address of the said software timer can be passed to the function
as an argument.
The implementation of these functions would utilize the address of the software timer in order
to do things like:
* creating timestamps
* creating delays etc.

*/

typedef struct
{
	uint32_t start; 
	uint32_t ticksToWait; 
	bool isCounting;
}sysTimer_t;


#endif //_SYSTIMER_STRUCT_H
