/*
 * app.h
 *
 *  Created on: Mar 23, 2021
 *      Author: akamb
 */

#ifndef APP_H_
#define APP_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

	void ledTask(uint32_t tick);
	void appTask(uint32_t tick);
	void appInit();


#ifdef __cplusplus
}
#endif



#endif /* APP_H_ */
