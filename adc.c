#include "stm32f10x.h"                  // Device header
#include "adc.h"

void ADC_Single_Conv_Init(ADC_TypeDef* adcPort, uint8_t channel, uint32_t sampleTime)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	
	//channel selected as 1st conversion in sequence
	adcPort->SQR3 = channel; 
	//configure sample time
	if (channel <= 9)
	{
		adcPort->SMPR2 = sampleTime; 
	}
	//turn ADC on, enable continuous mode
	adcPort->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT; 
	//turn ADC on again
	adcPort->CR2 |= ADC_CR2_ADON;
	//enable ADC calibration
	adcPort->CR2 |= ADC_CR2_CAL;
	while((adcPort->CR2 & ADC_CR2_CAL) == ADC_CR2_CAL);
}

uint16_t ADC_Read(ADC_TypeDef* adcPort)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	uint16_t data;
	//wait till end of conversion
	while((adcPort->SR & ADC_SR_EOC) != ADC_SR_EOC);
	data = adcPort->DR;
	return data;
}	
