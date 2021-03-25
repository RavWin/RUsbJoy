/*
 * app.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: akamb
 */

#include "app.h"
#include "usbd_hid.h"
#include "usb_device.h"
#include "adcHelper.h"
#include "adc.h"

#ifndef PACKED_STRUCT
    #define PACKED_STRUCT(__Declaration__)  __attribute__((packed)) __Declaration__;
#endif

extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct JoyData{
	uint16_t	x:		12;
	uint16_t	y:		12;
	uint16_t	z:		12;
	uint16_t	throttle: 12;
	uint8_t		buttons;
}PACKED_STRUCT(JoyData);

JoyData joyData;

void ledTask(uint32_t tick)
{
	static uint32_t lastSwitch = 0;
	static GPIO_PinState ledState = GPIO_PIN_RESET;
	if (ledState){
		if (tick > lastSwitch + 1900){
			lastSwitch = tick;
			ledState = GPIO_PIN_RESET;
		}
	}else
	{
		if (tick > lastSwitch + 100){
			lastSwitch = tick;
			ledState = GPIO_PIN_SET;
		}
	}
	HAL_GPIO_WritePin(LED_STAT_GPIO_Port, LED_STAT_Pin, ledState);
}

void appInit()
{
	MX_USB_DEVICE_Init();
	Adc::init();
}

void readJoyData()
{
	joyData.x = 4095-Adc::getValue(0);
	joyData.y = Adc::getValue(1);
	joyData.z = Adc::getValue(2);
	joyData.throttle = Adc::getValue(3);
	joyData.buttons = ! HAL_GPIO_ReadPin(JOY_BTN1_GPIO_Port, JOY_BTN1_Pin);
}

void appTask(uint32_t tick)
{
	static uint32_t lastSend = 0;
	if (tick > lastSend + 10){
		readJoyData();
		lastSend = tick;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &joyData, sizeof(joyData));
	}
}



