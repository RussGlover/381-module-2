/*
 * euclidean_direct.c
 *
 *  Created on: 2015-03-19
 *      Author: Aaron
 */

/*
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "sys/alt_dma.h"
#include "alt_types.h"

// flag used to indicate the transaction is complete
volatile int dma_complete = 0;

// function that is called when the transaction completes
void dma_done (void* handle, void* data){
	dma_complete = 1;
}

int main (void){
	alt_u16 buffer[16];
	alt_dma_rxchan rx;
	// Obtain a handle for the device
	if ((rx = alt_dma_rxchan_open ("/dev/dma_0")) == NULL){
		printf ("Error: failed to open device\n");
		exit (1);
	}
	else{
		// Post the receive request
		if (alt_dma_rxchan_prepare (rx, buffer, 16, dma_done, NULL) < 0){
			printf ("Error: failed to post receive request\n");
			exit (1);
		}
		// Wait for the transaction to complete
		while (!dma_complete);
		printf ("Transaction complete\n");
		alt_dma_rxchan_close (rx);
	}
	return 0;
}

*/
