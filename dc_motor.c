/*
 * dc_motor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: DELL
 */

#include "dc_motor.h"



void DcMotor_Init(void){
	/* setup the direction for the two motor pins through the GPIO driver */

	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_IN2, PIN_OUTPUT);

	/*Stop at the DC-Motor at the beginning through the GPIO driver */
	GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
	GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
}


void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if(speed<=0 && speed>=100){
		return;
	}
	Timer0_PWM_Start(speed);


	switch (state){
		case CW:
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_HIGH);
			break;
		case ACW:
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_HIGH);
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
			break;
		case STOP:
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
			break;
		default:
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
			GPIO_writePin( DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
			break;

	}

}




