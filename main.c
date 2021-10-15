#include <stdint.h>
#include <stdbool.h>
#include "sysTimer_struct.h"
#include "system.h"
#include "measure.h"

/*
CURRENT SENSOR: PA2
VOLTAGE DIVIDER: PA1
*/

uint16_t adcVoltage[NUMBER_OF_SAMPLES] = {0};
uint16_t adcCurrent[NUMBER_OF_SAMPLES] = {0};

typedef struct
{
	double voltage;
	double current;	
}room_t;


room_t room1;

int main(void)
{
	System_Init();
	voltageMeasurement_Init();
	
	
	while(1)
	{

		room1.voltage = getVoltage(adcVoltage);
		room1.current = getCurrent(adcCurrent);
		
	}
	
}
