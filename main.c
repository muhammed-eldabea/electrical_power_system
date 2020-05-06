/*
 * main.c
 *
 *  Created on: Feb 3, 2020
 *      Author: muhammed eldabea Hashem
 */


#include "ADC.h"
#include "ssp.h"
#include "app.h"
#include "dio.h"


int main ()
{

uint8 command ;
ADC_configuration config = {ADC_ps_by128,AVCC_with_external_capc } ;
volatile uint8 Data [11] = {0} ;
uint8 channel [11] = {tempr_sens_battery1,tempr_sens_battery2,current_sens1,current_sens2,current_sens3,current_sens4,current_sens5,voltage_sens1,voltage_sens2,voltage_sens3,voltage_sens4};

ssp_init() ;
ADC_init(&config) ;

/*
 * send data
 * select mode
 * 1-
 *
 * over volt (6v) ... turn of other subsytem
 *  OR over heat .... turn of other subsystem
 * if heat = 5 turn on heater
 * */

while(1)
{

	for (uint8 channel_num=0;channel_num<11;channel_num++)
	{
		Data[channel_num]=ADC_ReadAnalog(channel_num) ;
	}



sspGetData(EPS_Adresse,&command,1) ;

	switch (command)
	{

	case orbit_system :
      dio_toggle(orbit_system_pin) ;
      break ;
	case ADCS_system :
	dio_toggle(ADCS_system_pin) ;
	break ;
	case Communicatio_system :
		dio_toggle(Communicatio_system_pin) ;
		break ;
	case EPS_system :
		dio_toggle(EPS_system_pin) ;
		break ;
	case OBC_system :
		dio_toggle(OBC_system_pin) ;
		break ;
	case Strucutre_system :
		dio_toggle(Strucutre_system_pin)  ;
		break ;
	}

	if (command == OBC_ASK_for_Data)
	{

		ssp_send_data(OBC_Adresse,EPS_Adresse,OBC_ASK_for_Data,Data,11) ;

	}



	if ((Data[tempr_sens_battery1] < 25  ) || (Data[tempr_sens_battery2] < 25) )
	{
		dio_on(heater_pin) ;
		while ((Data[tempr_sens_battery1] < 30  ) || (Data[tempr_sens_battery2] < 30))
		{
		}
		dio_off(heater_pin) ;
		}

	if (((Data[tempr_sens_battery1] > 35  ) || (Data[tempr_sens_battery2] > 35)) || (Data[voltage_sens4] ==6) )
	{
		Dio_shutDown_all_system() ;
	}


}
}



