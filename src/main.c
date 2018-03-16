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

// Libraries
#include "u8g_arm.h"

// Private Function Declarations
static void STM32_initAllPeripherals(void);

// Private Data

// Tasks/Threads
static void GreenLedThread(void *arg);
static void OrangeLedThread(void *arg);

int main(void)
{
	STM32_initAllPeripherals();

	xTaskCreate(GreenLedThread, "Green LED Thread", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(OrangeLedThread, "Orange LED Thread", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);

	// Start the scheduler
	vTaskStartScheduler();

	return 0;
}
static u8g_t u8g;

// Private Function Definitions
static void STM32_initAllPeripherals(void)
{
	uint8_t errCode = 0;
	HAL_Init();

	GPIO_initPeripheral();
	errCode |= I2C_initPeripheral();
}

static void GreenLedThread(void *arg)
{
	while(1)
	{
		vTaskDelay(2000/portTICK_RATE_MS);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	}
}


static void draw(void)
{
    static uint8_t count = 0;
    count = (count > 200) ? 0 : count;

    u8g_SetFont(&u8g, u8g_font_helvB24);
    u8g_DrawStr(&u8g, 2, 24, "Hello :)");
    u8g_DrawStr(&u8g, 2, 48, u8g_u8toa(count++/20, 2));
}

/*
 * Brief: Thread responsible for drawing screen within the picture loop
 *        Performed at 10Hz (every 100ms)
 */
static void OrangeLedThread(void *arg)
{
	u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_i2c, u8g_com_hw_i2c_fn);

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		vTaskDelay(pdMS_TO_TICKS(50));
		u8g_FirstPage(&u8g);
		do
		{
		    draw();
		} while(u8g_NextPage(&u8g));
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}
