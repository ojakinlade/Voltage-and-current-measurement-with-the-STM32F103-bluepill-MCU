#ifndef _SYSTICK_H
#define _SYSTICK_H

//Initializes the systick timer on the stm32f103
extern void SysTick_Init(void);
//Gets the current tick i.e. timer count
extern uint32_t SysTick_GetTick(void);
//Creates a blocking delay in milliseconds
extern void SysTick_DelayMs(uint32_t delayTime);
/*Returns true if the systick timer has finished
counting for the period defined by the 'sysTimer_t'
software timer variable.
*/
extern bool SysTick_Timer_Done_Counting(sysTimer_t* pTimer);

#endif //_SYSTICK_H
