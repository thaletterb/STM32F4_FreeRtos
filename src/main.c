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

// Hardware
#include "SSD1306.h"

// Private Function Declarations
static void STM32_initAllPeripherals(void);

static const uint8_t logo16_glcd_bmp[] =
{
	0b00000000, 0b11000000,
	0b00000001, 0b11000000,
	0b00000001, 0b11000000,
	0b00000011, 0b11100000,
	0b11110011, 0b11100000,
	0b11111110, 0b11111000,
	0b01111110, 0b11111111,
	0b00110011, 0b10011111,
	0b00011111, 0b11111100,
	0b00001101, 0b01110000,
	0b00011011, 0b10100000,
	0b00111111, 0b11100000,
	0b00111111, 0b11110000,
	0b01111100, 0b11110000,
	0b01110000, 0b01110000,
	0b00000000, 0b00110000
};

// Tasks/Threads
static void GreenLedThread(void *arg);
static void OrangeLedThread(void *arg);

int main(void)
{
	//// set up interrupt priorities for FreeRTOS !!
	//HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	STM32_initAllPeripherals();

	//xTaskCreate(GreenLedThread, "Green LED Thread", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(OrangeLedThread, "Orange LED Thread", 2048, NULL, tskIDLE_PRIORITY + 1, NULL);

	// Start the scheduler
	vTaskStartScheduler();

	return 0;
}

// Private Function Definitions
static void STM32_initAllPeripherals(void)
{
	uint8_t errCode = 0;
	HAL_Init();

	GPIO_initPeripheral();
	errCode |= I2C_initPeripheral_defaults();
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
	SSD1306_init();

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		vTaskDelay(pdMS_TO_TICKS(1000));
		SSD1306_drawDataBuffer(SSD1306_getDisplayBufferHandle(), 1024);
	}
}
