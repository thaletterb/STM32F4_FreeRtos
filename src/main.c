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

// Drivers
#include "I2C_Driver.h"
#include "GPIO_Driver.h"

// Private Function Declarations
static void STM32_initAllPeripherals(void);

// Tasks/Threads
static void GreenLedThread(void *arg);
static void OrangeLedThread(void *arg);

int main(void)
{
	// set up interrupt priorities for FreeRTOS !!
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

	GPIO_initPeripheral();
	I2C_initPeripheral();
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
