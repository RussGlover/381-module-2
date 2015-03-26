//#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
//#include "sys/alt_irq.h"
//#include "system.h"
//#include <stdio.h>
//#include <unistd.h>
#include <stdbool.h>

#define GP_PIO_BASE (volatile char *) 0x00004880
#define switchAddress (volatile char *) 0x00048e0
#define ledAddress (char *) 0x00048b0
// defining pin numbers
/*
#define START_BIT 			14
#define WRITE_BIT 			13
#define DATA_BIT_0 			12
#define DATA_BIT_7 			5
#define INTERRUPT_BIT 		4
#define WAIT_BIT 			3
#define DATA_STROBE_BIT 	2
#define RESET_BIT 			1
#define ADDRESS_STROBE_BIT 	0
*/

#define START_BIT 			0
#define WRITE_BIT 			1
#define DATA_BIT_0 			2
#define DATA_BIT_7 			9
#define INTERRUPT_BIT 		10
#define WAIT_BIT 			11
#define DATA_STROBE_BIT 	12
#define RESET_BIT 			13
#define ADDRESS_STROBE_BIT 	14




#define READY 0
#define WAIT 1

#define IN 0
#define OUT 1

//Bit field defining the parallel port
typedef struct{
	unsigned short start 			: 1;
	unsigned short write 			: 1;
	unsigned short data 			: 8;
	unsigned short interrupt 		: 1;
	unsigned short wait 			: 1;
	unsigned short data_strobe 		: 1;
	unsigned short reset 			: 1;
	unsigned short address_strobe 	: 1;
} parallel_port;

typedef struct{
	unsigned char data;
	bool isAddress;
}readData;

/*Function to create a 16 bit value representing a parallel port configuration */
unsigned short setPort(parallel_port port)
{
    unsigned short temp = 0;
	
	temp = temp|(port.start << START_BIT);
	temp = temp|(port.write << WRITE_BIT);
	temp = temp|(port.data << DATA_BIT_7);
	temp = temp|(port.interrupt << INTERRUPT_BIT);
	temp = temp|(port.wait << WAIT_BIT);
	temp = temp|(port.data_strobe << DATA_STROBE_BIT);
	temp = temp|(port.reset << RESET_BIT);
	temp = temp|(port.address_strobe << ADDRESS_STROBE_BIT);

	return temp;
}
/*Bit extraction code taken from 
http://stackoverflow.com/questions/10090326/how-to-extract-specific-bits-from-a-number-in-c?rq=1
comment by kapilddit */
 /* Extracts bit at pos from MSB */

int extractBit(unsigned int data, int pos)
{
    if( !((pos >= 0) && (pos < 16)) )
    {
        return 0;
    }
    return ( ( data & (1<<(14 - pos) ) >> (14 - pos)));
}

unsigned int extractBitRange(unsigned int data, int startingPos, int offset)
{


   if(  !(((startingPos + offset) >= 0) && ( (startingPos + offset) <= 16)) )
   {
        return 0;
   }
   return ( data >> (14 - startingPos - offset) ) & ~(0xffffffff << (offset + 1));
}

unsigned short setBit(int pos) 
{
    if( !((pos >= 0) && (pos < 16)) )
    {
        return 0;
    }
    return ( 1<<pos );
}
