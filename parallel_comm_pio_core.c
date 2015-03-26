

#include "parallel_comm.h"

/* A variable to hold the value of the GP pio edge capture register. */
volatile int edge_capture;
/*Parallel port structs to store data on ports */
parallel_port current_parallel_port;

parallel_port parallel_port_inout;

/*******************************************************************
 * static void handle_gpio_interrupts( void* context, alt_u32 id)*
 *                                                                 *  
 * Handle interrupts from the gpios.                             *
 * This interrupt event is triggered by a button/switch press.     *
 * This handler sets *context to the value read from the button    *
 * edge capture register.  The button edge capture register        *
 * is then cleared and normal program execution resumes.           *
 * The value stored in *context is used to control program flow    *
 * in the rest of this program's routines.                         *
 *                                                                 *
 * Provision is made here for systems that might have either the   *
 * legacy or enhanced interrupt API active, or for the Nios II IDE *
 * which does not support enhanced interrupts. For systems created *
 * using the Nios II softawre build tools, the enhanced API is     *
 * recommended for new designs.                                    *
 ******************************************************************/

/*
#ifdef GP_PIO_BASE

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void handle_gpio_interrupts(void* context)
#else
static void handle_gpio_interrupts(void* context, alt_u32 id)
#endif
{
    /* Cast context to edge_capture's type. It is important that this be 
     * declared volatile to avoid unwanted compiler optimization.

    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Store the value in the Button's edge capture register in *context.
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(GP_PIO_BASE);
    /* Reset the Button's edge capture register.
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(GP_PIO_BASE, 0);
    
    /* 
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(GP_PIO_BASE); 
}

/* Initialize the button_pio. */

static void init_gpio()
{
	current_parallel_port.start 			= 0;
	current_parallel_port.write 			= 0;
	current_parallel_port.data 				= 0;
	current_parallel_port.interrupt 		= 0;
	current_parallel_port.wait 				= 0;
	current_parallel_port.data_strobe 		= 0;
	current_parallel_port.reset 			= 0;
	current_parallel_port.address_strobe 	= 0;
	
	
	/* Set inputs and outputs. By default data are inputs */
	parallel_port_inout.start 			= IN;
	parallel_port_inout.write 			= IN;
	parallel_port_inout.data 			= IN;
	parallel_port_inout.interrupt 		= OUT;
	parallel_port_inout.wait 			= OUT;
	parallel_port_inout.data_strobe 	= IN;
	parallel_port_inout.reset 			= IN;
	parallel_port_inout.address_strobe 	= IN;
	

	
    /* Recast the edge_capture pointer to match the alt_irq_register() function
     * prototype. */
    void* edge_capture_ptr = (void*) &edge_capture;
	/*Set the input and output ports. Sets the data pins and ground to outputs by default */
	/*To do: set data to constant */
	//IOWR_ALTERA_AVALON_PIO_DIRECTION(GP_PIO_BASE, 0x0018);
	IOWR_ALTERA_AVALON_PIO_DIRECTION(GP_PIO_BASE, 0x0000);
    /* Enable start pin[0] as interrupt */
    //IOWR_ALTERA_AVALON_PIO_IRQ_MASK(GP_PIO_BASE, 0x1);
	
	/* Set interrupt pin to 0 and wait pin to 1 */
	current_parallel_port.wait = WAIT;	
	IOWR_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE,0x0008);
	
}
    /* Reset the edge capture register by writing any value, as we haven't enabled bit-clearing
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(GP_PIO_BASE, 0x0);
    /* Register the interrupt handler.
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
    alt_ic_isr_register(GP_PIO_IRQ_INTERRUPT_CONTROLLER_ID, GP_PIO_IRQ, 
      handle_gpio_interrupts, edge_capture_ptr, 0x0);
#else
   /* alt_irq_register( GP_PIO_IRQ, edge_capture_ptr,
      handle_gpio_interrupts);
#endif */

//#endif GP_PIO_BASE




static void handle_start_interrupt(void)
{
	short switches;
	char leds = 255;

	switches = IORD_16DIRECT(switchAddress,0);

	//current_parallel_port.write = extractBit(switches,WRITE_BIT);

	current_parallel_port.write = extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),WRITE_BIT);

	/*If write bit is high then we are doing a write(Read from pi) */
    if( current_parallel_port.write )
	{
    	printf("Reading from DE2");
    	/*
		//Set data and ground to outputs
		parallel_port_inout.data = 0xff;
		IOWR_ALTERA_AVALON_PIO_DIRECTION(GP_PIO_BASE, setPort(parallel_port_inout));

		//set data from switches for test
		current_parallel_port.data = extractBitRange(IORD_16DIRECT(switchAddress,0),DATA_BIT_0,7);
		printf("Data is %i", current_parallel_port.data);
		//Display switch data on LEDS
		IOWR_8DIRECT(ledAddress,0,current_parallel_port.data);
		
		
		//Set wait to 0 and set data pins
		current_parallel_port.wait = READY;
		IOWR_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE, setPort(current_parallel_port));
		printf("Waiting for strobe");
		//wait till data_strobe or address_strobe goes low
		while( extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),ADDRESS_STROBE_BIT) && extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),DATA_STROBE_BIT) ) 
		{}
		printf("Strobed");
		//Set wait to 0
		current_parallel_port.wait = WAIT;
		IOWR_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE, setPort(current_parallel_port));
		printf("done");
		while(1);
	*/

	}
	//If write bit is low then we are doing a read(write from pi)
	else
	{
		printf("Writing from DE2");

		readData readInfo;
		// Set data and ground ports to inputs
		parallel_port_inout.data = 0x00;		
		IOWR_ALTERA_AVALON_PIO_DIRECTION(GP_PIO_BASE, 0x0018);
		
		//Set wait to 0
		current_parallel_port.wait = READY;
		IOWR_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE, 0x0000);
		printf("Ready");
		//wait till data_strobe or address_strobe goes low
		while( extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),ADDRESS_STROBE_BIT) && extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),DATA_STROBE_BIT) ) 
		{}

		//address read
		if(!extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),ADDRESS_STROBE_BIT))
		{
			readInfo.data = extractBitRange(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),DATA_BIT_0,7);
			readInfo.isAddress = 1;

		}
		else 
		{
			printf("Data:");
			int i;
			unsigned short bus;
			bus = IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE);
			for(i = 0; i <14 ; i++)
			{
				printf("%i ",extractBit(bus,i));
			}
			readInfo.data = extractBitRange(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),DATA_BIT_0,7);
			readInfo.isAddress = 0;
		}
		//Set wait to 1
		IOWR_8DIRECT(ledAddress,0,readInfo.data);
		current_parallel_port.wait = WAIT;
		IOWR_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE, 0xff);
	}
    printf("/n done /n");
    while(1){};
}

int main(void)
{
	unsigned short switches;
	printf("Starting GPIO intiate \n");
	init_gpio();
	printf("GPIO initiated\n");
	while(1)
	{
		usleep(1000000);



		switches = IORD_16DIRECT(switchAddress,0);
		int i;
		unsigned short bus;
		bus = IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE);

		for(i = 0; i <14 ; i++)
					{
						printf("%i ",extractBit(bus,i));
					}
		printf("\n");




		if ( extractBit(switches, START_BIT) )
			{
				printf("Checking for interrupt\n");

				if (extractBit(IORD_ALTERA_AVALON_PIO_DATA(GP_PIO_BASE),START_BIT))
				        {
							printf("Interrupt!\n");

				            handle_start_interrupt();
				        }

			}
	}
	return 0;
}



