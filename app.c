/*
 * app.c
 *
 *  Created on: Nov 24, 2020
 *      Author: BAHAA
 */

#include "int00.h"
#include "lcd.h"
#include "timer1.h"
/*
extern g_edgeCount;
extern g_timeHigh;
extern g_timePeriod;
extern g_timePeriodPlusHigh;
*/

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void){
	{
		//uint32 dutyCycle = 0;
		g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			//LCD_intgerToString(1);
			//_delay_ms(3000);
			TCNT1=0;
			/* Detect falling edge */
			MCUCR = (1<<ISC01);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = TCNT1;
			/* Detect rising edge */
			MCUCR |= (1<<ISC00) | (1<<ISC01);
		}
		else if(g_edgeCount == 3)
		{
			/* Store the Period time value */
			g_timePeriod = TCNT1;
			/* Detect falling edge */
			MCUCR = (1<<ISC01);
		}
		else if(g_edgeCount == 4)
		{
			/* Store the Period time value + High time value */
			g_timePeriodPlusHigh = TCNT1;
			/* Clear the timer counter register to start measurements again */
			TCNT1=0;
			/* Detect rising edge */
			MCUCR |= (1<<ISC00) | (1<<ISC01);
		}
	}

}

int main(){
	uint32 dutyCycle = 0;
	ConfigType Config = {F_CPU_CLOCK,RISING};

	//INT0_Init();
	INT00_Init();
	LCD_init();
	timer1_init(&Config);

	setCallBack(APP_edgeProcessing);

	while(1)
	{
		//LCD_goToRowColumn(0, 1);
		//LCD_intgerToString(g_edgeCount);

		if(g_edgeCount == 4)
		{
			SREG &= ~(1<<7);
			g_edgeCount = 0;
			LCD_displayString("Duty = ");
			/* calculate the dutyCycle */
			dutyCycle = ((float)(g_timePeriodPlusHigh-g_timePeriod) / (g_timePeriodPlusHigh - g_timeHigh)) * 100;
			/* display the dutyCycle on LCD screen */
			LCD_intgerToString(dutyCycle);
			LCD_displayCharacter('%');
		}
	}
}
