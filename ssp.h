/*
 * ssp.h
 *
 *  Created on: 9 Mar 2020
 *      Author: Muhammed Eldabea HAshem
 */

#ifndef SSP_H_
#define SSP_H_


#include "common_macros.h"
#include "microcontroller_config.h"
#include "std_types.h"

#define Baud_Rate 250000
#define ACK 0xff



#define FEND 0xc0
#define FESC 0xdb
#define TFEND 0xdc
#define TFESC 0xdd
#define PING_ssp_type 0
#define INIT_ssp_type 1
#define ACK_SSP_type 2
#define NACK_ssp_type 3
#define GET_ssp_type 4
#define PUT_ssp_type 5
#define Read_ssp_type 6
#define Write_ssp_type 7
#define ID_ssp_type 8
#define GET_EPS_telementry_type 9
#define PUT_EPS_telementry_Type 10
# define POLY 0x8408 /* bits reversed for LSB-first */
#define DataIsNotOK 0x88
#define DataISOK    0x57
#define StartCheck  0xcd




/**************************************/

#define tempr_sens_battery1  0
#define tempr_sens_battery2  1
#define current_sens1       2 /*bost cuurent*/
#define current_sens2       3
#define current_sens3       4
#define current_sens4       5
#define current_sens5       6
#define voltage_sens1       7      /*bost*/
#define voltage_sens2       8
#define voltage_sens3       9
#define voltage_sens4        10






void ssp_init() ;
void Send_data(unsigned char data ) ;
unsigned char Get_data() ;
uint8  ssp2bitcrc(uint8 * data, uint8 length) ;
void ssp_send_data(uint8 Dest_adresse , uint8 Source_Adresse , uint8 Type , volatile uint8 *data , uint8 legnth) ;
void sspGetData(uint8 Destination , uint8 *data , uint8 legnth) ;














#endif /* SSP_H_ */
