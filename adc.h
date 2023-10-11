 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	DIV_FACTOR_2=1,
	DIV_FACTOR_4,
	DIV_FACTOR_8,
	DIV_FACTOR_16,
	DIV_FACTOR_32,
	DIV_FACTOR_64,
	DIV_FACTOR_128,
}ADC_Prescaler;

/*
 * REFS1	REFS0
 * 0 		0 		AREF, Internal Vref turned off
   0 		1 		AVCC with external capacitor at AREF pin
   1 		0 		Reserved
   1 		1		Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
typedef enum{
	AREF,
	AVCC,
	RESERVED,
	INTERNAL_VOLTAGE,
}ADC_ReferenceVoltage;

typedef struct{
ADC_ReferenceVoltage ref_volt;
 ADC_Prescaler prescaler;
} ADC_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
