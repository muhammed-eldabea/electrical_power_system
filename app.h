/*
 * app.h
 *
 *  Created on: Feb 4, 2020
 *      Author: muhammed
 */

#ifndef APP_H_
#define APP_H_


#define tempr_sens_battery1  1
#define tempr_sens_battery2  2
#define current_sens1       1 /*bost cuurent*/
#define current_sens2       3
#define current_sens3       4
#define current_sens4       6
#define current_sens5       7
#define voltage_sens1       8      /*bost*/
#define voltage_sens2       3
#define voltage_sens3       5
#define voltage_sens4        6     /*battery voltage divider */
#define Communicatio_system  0x01
#define ADCS_system          0x02
#define orbit_system         0x03
#define Strucutre_system     0x04
#define OBC_system           0x05
#define EPS_system           0x06
#define OBC_ASK_for_Data     0x07
#define Communicatio_system_pin  0
#define ADCS_system_pin          1
#define orbit_system_pin         2
#define Strucutre_system_pin     3
#define OBC_system_pin           4
#define EPS_system_pin           5
#define heater_pin               6
#define Get                   0x05
#define Put                   0x59
#define OBC_Adresse   0x44
#define EPS_Adresse   0x55






#endif /* APP_H_ */
