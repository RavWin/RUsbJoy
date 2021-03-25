/*
 * adc.h
 *
 *  Created on: 14 ����. 2019 �.
 *      Author: Alex
 */

#ifndef ADCHELPER_H_
#define ADCHELPER_H_

#include "main.h"

#define ADC_CHANNELS_COUNT	4


#ifdef __cplusplus
extern "C" {
#endif

	void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);


#ifdef __cplusplus
}
#endif

namespace Adc{
	void 		init (void);
	uint16_t	getValue (uint8_t chan);
	uint16_t	getMeanValue(uint8_t chan);
}

#endif /* ADCHELPER_H_ */
