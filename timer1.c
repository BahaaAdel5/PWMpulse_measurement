/*
 * timer1.c
 *
 *  Created on: Nov 24, 2020
 *      Author: BAHAA
 */

#include "timer1.h"

void timer1_init(const ConfigType * Config_Ptr){
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);
	TCNT1 = 0;
}
