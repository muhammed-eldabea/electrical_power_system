/*
 * ssp.c
 *
 *  Created on: 9 Mar 2020
 *      Author: Muhammed Eldabea Hashem
 */


#include "ssp.h"

#define BaudRateValue  (((F_CPU / (Baud_Rate * 8UL))) - 1)

void ssp_init()
{
	/*configuration are :
	 * 1- 8_bit char size
	 * 2- no parity check
	 * 3- zero bit as stop bit
	 */


	UCSR0A |=(1<<1) ; /*enable double speed */

	UCSR0C |=(1<<1) ; /*enable Char size 0 */
	UCSR0C |=(1<<2) ; /*enable Char size 1 */

	UBRR0H = BaudRateValue>>8 ;
	UBRR0H = BaudRateValue ;
	UCSR0B |=(1<<4) ; /*enable RX */
	UCSR0B |=(1<<3) ; /*enable TX */


}


void Send_data(unsigned char data )
{
	UDR0 = data ;
	while(BIT_IS_CLEAR(UCSR0A,6)) {}
	SET_BIT(UCSR0A,6) ;
}

unsigned char Get_data()
{
	while (BIT_IS_CLEAR(UCSR0A,7)) {}
	SET_BIT(UCSR0A,7) ;
	return UDR0;
}


uint8  ssp2bitcrc(uint8 * data, uint8 length)
{
	uint8 crc = 0xff;
	uint8 *bufp = data;
	uint8 len;
	uint8 i;
	for (len = length; len > 0; len--)
	{
		uint8 ch = *bufp++;
		for (i = 8; i > 0; i--) {
			crc = (crc >> 1) ^ ( ((ch ^ crc) & 0x01) ? POLY : 0 );
			ch >>= 1;
		}
	}
	return crc;
}



void ssp_send_data(uint8 Dest_adresse , uint8 Source_Adresse , uint8 Type , volatile uint8 *data , uint8 legnth)
{
	volatile uint16 Frame[16] = {FEND} ;
	volatile uint8*ptrToFrame = Frame  ; /*a 8_ bit pointer to the frame  */
	volatile uint8 *ptrToData = data ;
	volatile uint8 stuffing_counter=0 ;
	uint8 Checkstate = 0 ;

	*ptrToFrame = FEND ;
	ptrToFrame++ ;
	*ptrToFrame=Dest_adresse ;
	ptrToFrame++ ;
	*ptrToFrame=Source_Adresse ;
	ptrToFrame++ ;
	*ptrToFrame = Type ;
	ptrToFrame++ ;

	for(uint8 inc = 0 ; inc <legnth ; inc++)
	{
		switch (*(ptrToData))
		{

		case FEND:

			*ptrToFrame=FESC ;
			ptrToFrame++ ;
			*ptrToFrame=TFEND ;
			ptrToFrame++  ;
			ptrToData++ ;
			stuffing_counter++ ;

			break;

		case FESC:

			*ptrToFrame=FESC ;
			ptrToFrame++ ;
			*ptrToFrame=TFESC ;
			ptrToFrame++  ;
			ptrToData++ ;
			stuffing_counter++ ;
			break;

		default:

			*ptrToFrame = *ptrToData  ;
			ptrToFrame++  ;
			ptrToData++ ;

			break;
		}

	}


	*ptrToFrame=ssp2bitcrc(data,legnth) ;
	ptrToFrame++ ;
	*ptrToFrame=FEND ;

	ptrToFrame = Frame  ;

	while(Get_data() != ACK) {}

	for (uint8 inc = 0 ; inc<(legnth+stuffing_counter+6) ; inc++)
	{
		Send_data(*(ptrToFrame)) ;

		ptrToFrame++ ;

		while(Get_data() != ACK) {}
	}

	while(Get_data()!=StartCheck) {}

	Checkstate = Get_data( ) ;

	switch(Checkstate)
	{

	case DataISOK :

		break ;

	case DataIsNotOK:

		ssp_send_data(Dest_adresse,Source_Adresse,Type,data,legnth) ;

		break ;


	}






}






void sspGetData(uint8 Destination , uint8 *data , uint8 legnth)
{
	volatile uint16 Frame[16] = {FEND} ;
	volatile uint8*ptrToFrame = Frame  ; /*a 8_ bit pointer to the frame  */
	volatile uint8 *ptrToData = data ;
	volatile uint8 counter = 0 ;
	volatile uint8 dataFromUart  ;
	uint8 oldCRC = 0 ;




	Send_data(ACK) ;

	*ptrToFrame = Get_data() ;

	ptrToFrame++ ;

	Send_data(ACK) ;

	while(dataFromUart != FEND)

	{
		dataFromUart = Get_data() ;
		*ptrToFrame=dataFromUart ;
		ptrToFrame++ ;
		Send_data(ACK) ;
	}


	ptrToFrame = Frame  ;

	ptrToFrame++ ;

	if(*ptrToFrame==Destination )

	{
		ptrToFrame++ ;
		ptrToFrame++ ;
		ptrToFrame++ ;


		for (uint8 inc = 0 ; inc<legnth ; inc++)
		{
			/*
			 * destuffing data
			 */

			if(*(ptrToFrame)==FESC)
			{
				switch(*(ptrToFrame+1))
				{

				case TFEND :
					*ptrToData=FEND ;
					ptrToFrame=ptrToFrame+2 ;
					ptrToData++ ;
					break ;
				case TFESC :
					*ptrToData=FEND ;
					ptrToFrame=ptrToFrame+2 ;
					ptrToData++ ;
					break ;

				}

			}

			else

			{

				*ptrToData=*ptrToFrame ;
				ptrToFrame++ ;
				ptrToData++ ;
			}
		}




		oldCRC = *(ptrToFrame+legnth) ;

		if(oldCRC==ssp2bitcrc(data,legnth))

		{
			Send_data(StartCheck) ;

			Send_data(DataISOK) ;

		}

		else

		{
			Send_data(StartCheck) ;

			Send_data(DataIsNotOK) ;

			sspGetData(Destination,data,legnth) ; /*call back to function to reget data*/



		}



	}

	else


	{
		Send_data(0xcc) ;
	}

}






