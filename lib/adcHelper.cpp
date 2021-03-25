/*
 * adc.c
 *
 *  Created on: 14 сент. 2019 г.
 *      Author: Alex
 */

#include <adcHelper.h>
#include "main.h"
#include "adc.h"

namespace Adc{

uint16_t buffer[ADC_CHANNELS_COUNT];	// ADC peripheral buffer
uint16_t data[ADC_CHANNELS_COUNT];		// saved ADC data
uint32_t accData[ADC_CHANNELS_COUNT] = {0};	// accumulated ADC data
uint32_t accCount[ADC_CHANNELS_COUNT] = {0};

/*
 * Получаем из буфера значения одного канала АЦП
 */
uint16_t getValue(uint8_t chan)
{
	if (chan < ADC_CHANNELS_COUNT)
		return data[chan];
	else
		return -1;
}

uint16_t	getMeanValue(uint8_t chan)
{
	if (!accCount[chan]) return getValue(chan);
	if (chan < ADC_CHANNELS_COUNT){
		uint16_t value = accData[chan] / accCount[chan];
		accCount[chan] = 0;
		accData[chan] = 0;
		return value;
	}
	else
		return -1;
}

void init(void)
{
	if (HAL_ADC_Start_DMA (&hadc1, (uint32_t*) buffer, ADC_CHANNELS_COUNT)
			!= HAL_OK) {
		/* Start Conversation Error */
		Error_Handler ();
	}
}

}// namespace Adc

/*
 * Функция вызывается по прерыванию DMA
 * Если не использовать буферизацию, то в измерениях
 * появляются пропуски (нулевые значения)
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	for (int i = 0; i < ADC_CHANNELS_COUNT; i++) {
		Adc::data[i] = Adc::buffer[i];  // store the values in buffer[]
		Adc::accData[i] += Adc::buffer[i];
		Adc::accCount[i]++;
	}
}
