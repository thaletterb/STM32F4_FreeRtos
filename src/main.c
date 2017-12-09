/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"

// Private Function Declarations
static void STM32_initAllPeripherals(void);
static void STM32_initGPIOPeripheral(void);

// Tasks/Threads
static void GreenLedThread(void *arg);
static void OrangeLedThread(void *arg);


int main(void)
{
	// set up interrupt priorities for FreeRTOS !!
	//NVIC_PriorityGroupConfig( NVIC_PRIORITYGROUP_4 );
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	STM32_initAllPeripherals();

	xTaskCreate(GreenLedThread, "Green LED Thread", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(OrangeLedThread, "Orange LED Thread", 128, NULL, tskIDLE_PRIORITY + 1, NULL);


	// Start the scheduler
	vTaskStartScheduler();

	return 0;
}

// Private Function Definitions
static void STM32_initAllPeripherals(void)
{
	HAL_Init();

	STM32_initGPIOPeripheral();
}

static void STM32_initGPIOPeripheral(void)
{
	// Enable clock to GPIOD peripheral
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// GPIOD Configuration
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin 	= GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed 	= GPIO_SPEED_MEDIUM; //GPIO_Speed_50MHz;
	GPIO_InitStruct.Pull 	= GPIO_PULLUP; //GPIO_PuPd_UP;
//
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

static void GreenLedThread(void *arg)
{
	while(1)
	{
		vTaskDelay(250/portTICK_RATE_MS);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	}
}

static void OrangeLedThread(void *arg)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
