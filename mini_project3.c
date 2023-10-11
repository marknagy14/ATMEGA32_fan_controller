/*
 * mini_project3.c
 *
 *  Created on: Oct 11, 2023
 *      Author: DELL
 */

#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "adc.h"
#include <avr/io.h>

typedef enum{
	FAN_OFF,FAN_ON
}Fan_State;

Fan_State state;

void control_fan(uint8 temp) {

	if (temp < 30) {
		state = FAN_OFF;
		DcMotor_Rotate(STOP, 0);
	} else if (temp >= 30 && temp < 60) {
		state = FAN_ON;
		DcMotor_Rotate(CW, 25);
	} else if (temp >= 60 && temp < 90) {
		state = FAN_ON;
		DcMotor_Rotate(CW, 50);
	} else if (temp >= 90 && temp < 120) {
		state = FAN_ON;
		DcMotor_Rotate(CW, 75);
	} else if (temp >= 120) {
		state = FAN_ON;
		DcMotor_Rotate(CW, 100);
	}

}

int main(void) {
	uint8 temp;

	ADC_ConfigType adc_configurations = { INTERNAL_VOLTAGE, DIV_FACTOR_8 };
	state = FAN_OFF;

	LCD_init();
	ADC_init(&adc_configurations);
	DcMotor_Init();
	SREG |= (1<<7);

	LCD_displayStringRowColumn(0, 0, "FAN IS    ");
	LCD_displayStringRowColumn(1, 0, "Temp =    C");

	while (1) {
		temp = LM35_getTemperature();
		control_fan(temp);

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1, 7);
		if (temp >= 100) {
			LCD_intgerToString(temp);
		} else {
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		if (state == FAN_ON) {
			LCD_moveCursor(0, 7);
			LCD_displayString("ON ");
		} else {
			LCD_moveCursor(0, 7);
			LCD_displayString("OFF");
		}

	}

}

