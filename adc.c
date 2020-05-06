/**********************************************************
 * ADC2560.h                                              *
 *                                                        *
 *  Created on: Jan 20, 2020                              *
 *      Author: muhammed eldabea hashem                   *
 **********************************************************/





/******************************************INCLUDE****************************/

#include "ADC.h" /*include ADC library */


/*****************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/**************************************Founction******************************/


#ifdef ADC_Interrupt_enable
ISR (ADC_vect)
{
	if(g_callBackPtr |= NULL_PTR)
	{
		(*g_callBackPtr)() ;
	}


}

#endif


void ADC_init(ADC_configuration *ADC_ptr)
{

	/**************************************************************************************************
	 *[FunctionName] :  ADC_init                                                                      *
	 *[description]  :  used to init the ADC module                                                   *
	 *[parameter]    :  take a structure that have(prescaler,refernece power,autotrigger,DIDR         *
	 *[Return]       :  void                                                                          *
	 *************************************************************************************************/



	ADMUX = (ADMUX & 0x3F) | ((ADC_ptr->ADC_refernePower &0x03)<<6) ; /*configure the reference voltage source of ADC */


#ifdef ADC_left_Adjustment_result

	SET_BIT(ADMUX,5) ;  /*enable the left adjustment for result .. normally right adjustment is enabled*/

#endif



#ifdef ADC_Auto_trigger_enable

	ADCSRA |=(1<<5) ; /*enable auto trigger source*/

#endif


#ifdef ADC_Interrupt_enable
	ADCSRA |=(1<<3) ; /*enable adc interrupt request*/
	SREG |=(1<<7) ;/*Enable interrupt request in general statue register */
#endif

	ADCSRA = (ADCSRA &0xF8 ) | (ADC_ptr->ADC_preScaler &0x07) ; /*prescaler value*/

	ADCSRA |=(1<<7) ; /*enable the ADC module*/

}



void ADC_CallBack(void(*ptr2foun)(void))
{


	/**************************************************************************************************
	 *[FunctionName] :  ADC_callback                                                                  *
	 *[description]  :  used to send function tobe handeled bu ISR                                    *
	 *[parameter]    :  take a pointer to founction that will be excuted in ADC_interrupt             *
	 *[Return]       :  void                                                                          *
	 **************************************************************************************************/




	g_callBackPtr=ptr2foun ;

}







uint16 ADC_ReadAnalog(uint8 channel_number)
{


	/**************************************************************************************************
	 *[FunctionName] :  ADC_ReadAnalod                                                                *
	 *[description]  :  used to Read tha  analog data                                                 *
	 *[parameter]    :  take a channel number                                                         *
	 *[Return]       :  data with 16 bit size                                                         *
	 **************************************************************************************************/

	ADMUX = (ADMUX & 0xE0 ) |  (channel_number &0x1F) ; /*Configure the channel will be used ..first 4 bits   */

	ADCSRB = (ADCSRB & 0xf7) | ((channel_number &0x20 )>>2) ; /*Configure the channel will be used ..only 5th bit*/


	ADCSRA |=(1<<6) ;  /*set start conversion bit */
	while(BIT_IS_CLEAR(ADCSRA,4)) {} /*wait until conversion finished*/
	SET_BIT(ADCSRA,4) ; /*clear ADCIF bit (flag bit)*/
	return ADC ;   /*return data */


}





uint16 Get_temp (uint8 channel)

{ uint16 temprt ;
	temprt=ADC_ReadAnalog(channel)/2.05 ;
	return temprt ;
}

uint16 Get_volt (uint8 channel)

{ uint16 volt ;
	volt=(ADC_ReadAnalog(channel)*5)/1012 ;
	return volt ;
}

uint16 Get_BidirectionalCurrent (uint8 channel)

{ uint16 BidirectionalCurrent ;
   uint16 calculated_value = (ADC_ReadAnalog(channel)-2.5)/(.4) ;
   BidirectionalCurrent=(calculated_value*5)/1024 ;
	return BidirectionalCurrent ;
}
uint16 Get_onedirectionalCurrent (uint8 channel)

{ uint16 onedirectionalCurrent ;
   uint16 calculated_value = (ADC_ReadAnalog(channel))/(.2) ;
   onedirectionalCurrent=(calculated_value*5)/1024 ;
	return onedirectionalCurrent ;
}









