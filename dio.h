/*
 * dio.h
 *
 *  Created on: Feb 4, 2020
 *      Author: muhammed
 */

#ifndef DIO_H_
#define DIO_H_

#define Control_Data_direction DDRA
#define Control_port           PORTA



#include "std_types.h"
#include "common_macros.h"
#include "microcontroller_config.h"


void Dio_shutDown_all_system () ;
void dio_toggle (uint8 channel) ;
void dio_on (uint8 channel  ) ;
void dio_off (uint8 channel ) ;
void dioinit () ;

#endif /* DIO_H_ */
