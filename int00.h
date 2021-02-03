/*
 * int00.h
 *
 *  Created on: Nov 25, 2020
 *      Author: BAHAA
 */

#ifndef INT00_H_
#define INT00_H_


#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

void INT00_Init(void);
void setCallBack(void(*a_ptr)(void));


#endif /* INT00_H_ */
