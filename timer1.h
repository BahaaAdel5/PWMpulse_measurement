/*
 * timer1.h
 *
 *  Created on: Nov 24, 2020
 *      Author: BAHAA
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Clock;

typedef enum
{
	FALLING,RISING
}EdgeType;

typedef struct
{
	Clock clock;
	EdgeType edge;
}ConfigType;


void timer1_init(const ConfigType * Config_Ptr);

#endif /* TIMER1_H_ */
