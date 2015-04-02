/*
 * euclidean.c
 *
 *  Created on: 2015-03-19
 *      Author: Aaron
 */

#include "inttypes.h"
#include "euclidean.h"
#include <stdint.h>
#include <stdio.h>
#define euclideanAddress (volatile int *) 0x4920
// A test of running only 1 16bit bin on another 16bit bin

int euclideanS(unsigned short int library, unsigned short int toCompare){

	unsigned short int curLib, curComp;
	unsigned int input = 0;
	unsigned int result = 0;

		curLib = library;
		curComp = toCompare;
		printf("curLib is %u curComp is %u ", curLib, curComp);

		input = curLib;
		input <<= 16;
		input = (input | curComp);
		IOWR_32DIRECT(euclideanAddress, 0, input);


		//usleep(50000);
		result = (unsigned int) IORD_32DIRECT(euclideanAddress,0);
		printf ("current result is %u ", result);
		//testing[j] = IORD_32DIRECT(euclideanAddress, 0);


	return result;
}

//Using EuclideanSingle component but handles 8bins against 8bins on software side
unsigned long long euclideanSingle(unsigned short library[8], unsigned short toCompare[8]){
	unsigned int j = 0;
	unsigned int testing[8];
	unsigned short int curLib, curComp;
	unsigned int input;
	unsigned long long result = 0;
	for (j = 0; j <8; j++){
		curLib = library[j];
		curComp = toCompare[j];
		//printf("curLib is %u curComp is %u ", curLib, curComp);

		input = curLib;
		input <<= 16;
		input = (input | curComp);

		IOWR_32DIRECT(euclideanAddress, 0, input);


		//usleep(50000);
		result += (unsigned long long) IORD_32DIRECT(euclideanAddress,0);
		//printf ("current result is %llu ", result);
		//testing[j] = IORD_32DIRECT(euclideanAddress, 0);
	}

	return result;
}


//8 bins against 8 bins with hardware component, currently not working.
unsigned long long euclideanCalc(unsigned short library[8], unsigned short toCompare[8]){
	unsigned int j;
	unsigned int testing;
	unsigned short int curLib, curComp;
	unsigned int input;


	for (j = 0; j < 8; j++){



		IOWR_8DIRECT(euclideanAddress, 0, library[j]);
		IOWR_8DIRECT(euclideanAddress, 8, toCompare[j]);
		//unsigned long long 64
		//unsigned short int 16
		usleep (5000);
		testing = IORD_32DIRECT(euclideanAddress, 0);
		printf ("current is %d", testing);

	}

	//usleep(5000);
	unsigned long long temp1;
	unsigned long long temp2;
	unsigned long long result = 0;
	temp1 = IORD_32DIRECT(euclideanAddress, 0);
	temp2 = IORD_32DIRECT(euclideanAddress, 32);
	temp2 = temp2<<32;
	result = temp1 | temp2;
	return result;
}


