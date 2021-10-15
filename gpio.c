#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "gpio.h"

void GPIO_Reset(GPIO_TypeDef* gpioPort)
{
	/*
	Description:
	Resets specific bits in the GPIO registers prior to input or output mode
	configuration. PA13,PA14,PA15,PB2,PB3 and PB4 are left in their reset states.
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	Return:
	None
	
	*/
	
	if (gpioPort == GPIOA)
	{
		gpioPort->CRL &= ~0xCCCCCCCC;
		gpioPort->CRH &= ~0x000CCCCC;
	}
	
	else if (gpioPort == GPIOB)
	{
		gpioPort->CRL &= ~0xCCC000CC;
		gpioPort->CRH &= ~0xCCCCCCCC;
	}
	
	else
	{
		gpioPort->CRL &= ~0xCCCCCCCC;
		gpioPort->CRH &= ~0xCCCCCCCC;
	}
	
}

void GPIO_Input_Init(GPIO_TypeDef* gpioPort, 
										 uint8_t portLevel, 
										 uint8_t gpioPin,
										 uint32_t config,  
										 bool pullupEn)
											 
{
	/*
	Description:
	Initializes GPIO peripheral to an input mode
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	2.) portLevel: The GPIO port configuration register is either low or high
	depending on the set of GPIO pins used e.g. Pins 0-7 are configurable using
	GPIOx_CRL register while Pins 8-15 are configurable using GPIOx_CRH register.
	Depending on the pins being used, 'portLevel' is passed with an argument which
	determines whether GPIOx_CRL or GPIOx_CRH register is configured.
	
	If portLevel is passed with GPIO_PORT_REG_LOW, the GPIOx_CRL register is configured.
	If portLevel is passed with GPIO_PORT_REG_HIGH, the GPIOx_CRH register is configured.
	
	3.) gpioPin: Pin number of GPIO input pin e.g. if this parameter is passed with 
	GPIO_PINx, pin x will be written high if 'pullupEn' is true.
	
	4.) config: If this parameter is passed with GPIO_PINx_INPUT_PULLUP_OR_PULLDOWN, the 
	GPIOx_CRL or GPIOx_CRH register sets pin x to an input mode with pull-up or pull-down.
	If this parameter is passed with 'GPIO_ANALOG_MODE', the GPIOx_CRL or GPIOx_CRH register
	sets pin x to analog mode
	
	5.) pullupEn: If this parameter is set 'true', bit x of the GPIO_ODR register is set high
	to enable internal pull-up resistor provided the config parameter is passed with
	GPIO_PINx_INPUT_PULLUP_OR_PULLDOWN
	
	Return:
	None
	
	*/
	volatile uint32_t* pGpioConfigReg = &gpioPort->CRL;
	
	if (portLevel == GPIO_PORT_REG_HIGH)
	{
		pGpioConfigReg = &gpioPort->CRH;
	}
	
	*pGpioConfigReg |= config;
	
	if (pullupEn)
	{
		gpioPort->ODR |= (1<<gpioPin);
	}
}

void GPIO_Output_Init(GPIO_TypeDef* gpioPort,
										  uint8_t portLevel,
											uint32_t mode,
											uint32_t config)

{
	/*
	Description:
	Initializes GPIO peripheral to an output mode
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	2.) portLevel: The GPIO port configuration register is either low or high
	depending on the set of GPIO pins used e.g. Pins 0-7 are configurable using
	GPIOx_CRL register while Pins 8-15 are configurable using GPIOx_CRH register.
	Depending on the pins being used, 'portLevel' is passed with an argument which
	determines whether GPIOx_CRL or GPIOx_CRH register is configured.
	
	3.) mode: Configures the GPIO output mode speed e.g. if this parameter is passed
	with GPIO_PINx_OUTPUT_MODE_2MHZ, GPIO pin x is configured in output mode with a
	maximum speed of 2MHz. Multiple GPIO pins of the same port can be logically ORed
	to get their output mode configured.
	
	4.) config: Configures the type of GPIO output e.g. general purpose push-pull,
	general purpose open-drain, alternate function push-pull and alternate function
	open-drain. If this parameter is passed with GPIO_PINx_ALT_FUNC_OPEN_DRAIN, 
	GPIO pin x will be configured as an alternate function output open drain pin.
	
	Return:
	
	*/
	volatile uint32_t* pGpioConfigReg = &gpioPort->CRL;
	
	if (portLevel == GPIO_PORT_REG_HIGH)
	{
		pGpioConfigReg = &gpioPort->CRH;
	}
	
	*pGpioConfigReg |= mode;
	*pGpioConfigReg |= config;
}

void GPIO_Output_Write(GPIO_TypeDef* gpioPort,
															uint8_t gpioPin,
															bool gpioPinLogic)
																
{
	
	/*
	Description:
	Writes a logic 'high' or 'low' to a GPIO pin
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	2.) gpioPin: Pin number of GPIO output pin e.g. if this parameter is passed with 
	GPIO_PINx, pin x will be driven high if 'gpioPinLogic' is true else pin x will
	be driven low.
	
	3.) gpioPinLogic: If this parameter is set 'true', bit x of the GPIO_ODR 
	register is set high otherwise, it is set 'low'.
	
	Return:
	None
	
	*/
	
	gpioPort->ODR &= ~(1<<gpioPin);
	
	if (gpioPinLogic)
	{
		gpioPort->ODR |= (1<<gpioPin);
	}
	
}

void GPIO_Output_Clear_Reg(GPIO_TypeDef* gpioPort,
													 uint32_t gpioPins)
{
	gpioPort->ODR &= ~gpioPins;
}

void GPIO_Output_Reg_Write(GPIO_TypeDef* gpioPort,
													 uint32_t gpioPins)
{
	gpioPort->ODR |= gpioPins;
}

bool GPIO_Input_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin)
{
	/*
	Description:
	Reads a GPIO pin and returns its logic level or state
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	2.) gpioPin: Pin number of GPIO input pin e.g. if this parameter is passed with 
	GPIO_PINx, the state of pin x will be read
	
	Return:
	1.) true if GPIO pin is high
	2.) false if GPIO pin is low
	
	*/
	
	if ( (gpioPort->IDR & (1<<gpioPin)) == (1<<gpioPin) )
	{
		return true;
	}
	
	return false;
}

bool GPIO_Output_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin)
{
	if ( (gpioPort->ODR & (1<<gpioPin)) == (1<<gpioPin) )
	{
		return true;
	}
	
	return false;	
}
	
