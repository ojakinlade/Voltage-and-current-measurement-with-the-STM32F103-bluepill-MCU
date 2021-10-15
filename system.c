#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "clocks.h"
#include "gpio.h"
//#include "iwdg.h"
#include "sysTimer_struct.h"
#include "systick.h"
#include "system.h"

void System_Init(void)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	
	Clocks_Init();
	SysTick_Init();
	GPIO_Reset(GPIOA);
	GPIO_Reset(GPIOB);
	GPIO_Reset(GPIOC);
}

void System_Timer_DelayMs(uint32_t delayTime)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	
	SysTick_DelayMs(delayTime);
}

void System_Alarm_Init(sysTimer_t* pSysTimer, uint32_t timerRepTime)
{
	pSysTimer->start = 0;
	pSysTimer->isCounting = false;
	pSysTimer->ticksToWait = timerRepTime;
}

bool System_Alarm_Ready(sysTimer_t* pSysTimer)
{
	bool countingComplete = false;
	
	if (!pSysTimer->isCounting)
	{
		pSysTimer->start = SysTick_GetTick();
		pSysTimer->isCounting = true;
	}
	
	else
	{
		if ( SysTick_Timer_Done_Counting(pSysTimer) )
		{
			countingComplete = true;
			pSysTimer->start = 0;
			pSysTimer->isCounting = false;
		}
	}
	
	return countingComplete;
}

//void System_Watchdog_Start(void)
//{
//	/*
//	Description:
//	
//	Parameters:
//	
//	Return:
//	
//	*/
//	
//	IWDG_Start();
//}

//void System_Watchdog_Refresh(void)
//{
//	/*
//	Description:
//	
//	Parameters:
//	
//	Return:
//	
//	*/
//	
//	IWDG_Refresh();
//}
//	
