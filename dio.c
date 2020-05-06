/*
 * dio.c
 *
 *  Created on: Feb 4, 2020
 *      Author: muhammed
 */

#include "dio.h"


void dioinit ()
{

	Control_Data_direction = 0x7f ;
    Control_port = 0x1f ;

}

void dio_off (uint8 channel )
{

	CLEAR_BIT(Control_port,channel) ; /*turn of any pin */
}


void dio_on (uint8 channel  )
{


	SET_BIT(Control_port,channel) ;
}



void dio_toggle (uint8 channel)
{


	TOGGLE_BIT(Control_port,channel) ;

}

void Dio_shutDown_all_system ()
{

	Control_port=0x30 ;
}
