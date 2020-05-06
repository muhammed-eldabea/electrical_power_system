/**********************************************************
 * ADC2560.h                                              *
 *                                                        *
 *  Created on: Jan 20, 2020                              *
 *      Author: muhammed eldabea hashem                   *
 **********************************************************/


/*******************************************************************************************************/


#ifndef ADC_H_
#define ADC_H_


/*****************************************INCLUDE********************************/
#include "std_types.h"
#include "avr/io.h"
#include "avr/delay.h"
#include "common_macros.h"
#include "avr/interrupt.h"

/*************** ***********************Defination******************************/

#define NULL_PTR (void*)0
/*******************************************************************************
 * you can define these to enable founction ;                                   *
 * 1-ADC_Interrupt_enable                                                       *
 * 2-ADC_left_Adjustment_result                                                 *
 * 3-ADC_Auto_trigger_enable                                                    *
 ********************************************************************************/


/***************************************************************************************/

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;



typedef enum
/*used to chose the refernce voltage*/
{AREF_interneal_Vref_turned_off,AVCC_with_external_capc,
	internal_1_1,internal_2and56} refernce_voltag_chose ;


typedef enum
/*select ADC channel */
{ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC0_postoADC0_neg_gain10x,ADC1_postoADC0_neg_gain10x,
	ADC0_postoADC0_neg_gain200x,ADC1_postoADC0_neg_gain200x,ADC2_postoADC2_neg_gain10x,ADC3_postoADC2_neg_gain10x,
	ADC2_postoADC2_neg_gain200x,ADC3_postoADC2_neg_gain200x,ADC0_postoADC1_neg_gain1x,ADC1_postoADC1_neg_gain1x,
	ADC2_postoADC1_neg_gain1x,ADC3_postoADC1_neg_gain1x,ADC4_postoADC1_neg_gain1x,ADC5_postoADC1_neg_gain1x,
	ADC6_postoADC1_neg_gain1x,ADC7_postoADC1_neg_gain1x,ADC0_postoADC2_neg_gain1x,ADC1_postoADC2_neg_gain1x,
	ADC2_postoADC2_neg_gain1x ,ADC3_postoADC2_neg_gain1x,ADC4_postoADC2_neg_gain1x,ADC5_postoADC2_neg_gain1x,VBG1_1ADC,
	GND_ADC,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13,ADC14,ADC15,ADC8_postoADC8_neg_gain10x ,ADC9_postoADC8_neg_gain10x,
	ADC8_postoADC8_neg_gain200x,ADC9_postoADC8_neg_gain200x,ADC10_postoADC10_neg_gain10x,ADC11_postoADC10_neg_gain10x,
	ADC10_postoADC10_neg_gain200x,ADC11_postoADC10_neg_gain200x,ADC8_postoADC9_neg_gain1x,ADC9_postoADC9_neg_gain1x,
	ADC10_postoADC9_neg_gain1x,ADC11_postoADC9_neg_gain1x,ADC12_postoADC9_neg_gain1x,ADC13_postoADC9_neg_gain1x,
	ADC14_postoADC9_neg_gain1x,ADC15_postoADC9_neg_gain1x,ADC8_postoADC10_neg_gain1x,ADC9_postoADC10_neg_gain1x,
	ADC10_postoADC10_neg_gain1x,ADC11_postoADC10_neg_gain1x,ADC12_postoADC10_neg_gain1x,ADC13_postoADC10_neg_gain1x,
	ADC_RESERVER1,ADC_RESERVER2
}ADC_channel;


typedef enum
/*used to chose the prescaler value as frequency always should be between 125khz and 250khz*/
{ADC_ps_by2,ADC_ps_by2r,ADC_ps_by4,ADC_ps_by8,
	ADC_ps_by16,ADC_ps_by32,ADC_ps_by64,ADC_ps_by128
}ADC_preScaler;


typedef enum
/*conversion will be trigger by rising edge of selected interrupt flag
 * select the trigger source and enable ADATE bit in ADSERA will make ADC start conversion at positive edge
 * of the selecting edge
 * Rather than enable ADC  manually it will be trigger depending on a External source
 * */
{
	ADC_free_running_mode,ADC_analog_comparator,adc_external_interrupt_request,ADCtimer0_compare_match,
	ADC_timer0_overFlow,timer1_compareMatch,ADCtimer1_overFlow,Timer1CaptureEvent,ADCAutoTrigger_OFF
}ADC_AutoTrigger_Source;


typedef enum
/*Digital Disable input mean we we use pin in pins for aim for ADC we will Stop digital buffer
 *as digital buffer take more much power that is not be used while ADC conversion function
 *this option will stop working of Digital buffer
 * */
{
ADC0DD,ADC1DD,ADC2DD,ADC3DD,ADC4DD,ADC5DD,ADC6DD,ADC7DD,
ADC8DD,ADC9DD,ADC10DD,ADC11DD,ADC12DD,ADC13DD,ADC14DD,ADC15DD
}ADC_Digital_input_Disable;




/***************************************STRUCTURE******************************/
typedef struct
{

	uint8 ADC_preScaler ; /*ADC prescaler of frequency divider  */
	uint8 ADC_refernePower; /*used to reference a volt to ADC module  */



}ADC_configuration;

/*********************************FounctionProtype****************************/


void ADC_init(ADC_configuration *ADC_ptr) ;
void ADC_CallBack(void(*ptr2foun)(void)) ;
uint16 ADC_ReadAnalog(uint8 channel_number) ;
uint16 Get_onedirectionalCurrent (uint8 channel) ;
uint16 Get_BidirectionalCurrent (uint8 channel) ;
uint16 Get_volt (uint8 channel) ;
uint16 Get_temp (uint8 channel) ;

/****************************************************************************************************************/






#endif /* ADC_H_ */
