#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "sysTimer_struct.h"
#include "systick.h"

static volatile uint32_t numberOfTicks = 0;

void SysTick_Init(void)
{
	/*
	Description:
	Initializes systick timer
	
	Parameters:
	None
	
	Return:
	None
	
	*/
	
	//Systick default clock source = AHB/8 = 1MHz
	SysTick->LOAD = 1000 - 1; //1ms timebase
	SysTick->VAL = 0;
	SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk); //Enable systick interrupt and systick timer
}

uint32_t SysTick_GetTick(void)
{
	/*
	Description:
	Gets current tick (or count or clock cycle) of the systick timer.
	The tick is equal to the value of the 'numberOfTicks' variable which
	is increment by the systick interrupt service routine.
	
	Parameters:
	None
	
	Return:
	Current tick
	
	*/
	return numberOfTicks;
}

void SysTick_DelayMs(uint32_t delayTime)
{
	/*
	Description:
	Creates a delay in milliseconds. This delay is a busy-wait
	mechanism hence it blocks other tasks from being executed
	while the CPU is waiting for the delay time to elapse
	
	Parameters:
	1.) delayTime: time in milliseconds through which the delay
	lasts.
	
	Return:
	None
	
	*/
	uint32_t startTick = numberOfTicks;
	while((numberOfTicks - startTick) < delayTime){}
}

bool SysTick_Timer_Done_Counting(sysTimer_t* pTimer)
{
	/*
	Description:
	Function to determine whether a software timer of
	the type 'sysTimer_t' is done counting.
	
	Parameters:
	1.) pTimer: pointer to a software timer of the type
	'sysTimer_t'. This parameter is passed with the address
	of a software timer that is used to periodically run a
	block of code.
	
	Return:
	1.) true: if software timer (whose address is passed as an 
	argument) is done counting.
	2.) false: if the software timer is still counting.
	
	*/
	bool countingComplete = false;
		
	if ( (SysTick_GetTick() - pTimer->start) >= pTimer->ticksToWait )
	{
		countingComplete = true;
	}
	
	return countingComplete;
}

void SysTick_Handler(void)
{
	/*
	Description:
	Systick timer interrupt service routine
	
	Parameters:
	None
	
	Return:
	None
	
	*/
	numberOfTicks++;
}
