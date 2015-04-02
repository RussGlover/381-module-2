/*
 * testEmain.c
 *
 *  Created on: 2015-03-12
 *      Author: Aaron
 */



#include "inttypes.h"
#include "headers.h"
#include <stdint.h>
#include <stdio.h>

int main()
{
	unsigned short testLibrary[8];
	unsigned short testCompareEqual[8];
	unsigned short testCompareDiff[8];
	unsigned short testLibrary2[8];
	unsigned short testData[8];
	unsigned short testData2[8];

	unsigned short testL = 4;
	unsigned short testC = 1;
	unsigned int i;

	//printf("Hello");
	//unsigned int resultsingle;
	//resultsingle = euclideanS(testL, testC);
	//printf("Difference is %u", resultsingle);

	for (i = 0; i < 8; i++){
		testLibrary[i] = 2000;
		testCompareEqual[i] = 2000;
		testCompareDiff[i] = 1000;
		testLibrary2[i] = 100*i;
		testData[i] = 100*i;
		testData2[i] = 100;
	}

	unsigned long long testEqual = euclideanSingle(testLibrary, testCompareEqual);
	unsigned long long testDiff = euclideanSingle(testLibrary, testCompareDiff);
	unsigned long long testEqual2 = euclideanSingle(testLibrary2, testData);
	unsigned long long testDiff2 = euclideanSingle(testLibrary2, testData2);


	printf("Distance Equal: %llu, Distance Diff: %llu\n", testEqual, testDiff);

	printf("Distance Equal2: %llu, Distance Diff2: %llu\n", testEqual2, testDiff2);

	//printf("Distance Diff: %llu\n",  testDiff);
	return 0;
}







/*
// A test of running only 1 16bit bin on another 16bit bin
int euclideanS(unsigned short library, unsigned short toCompare){

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
int euclideanCalc(unsigned short library[8], unsigned short toCompare[8]){
	unsigned int j;
	unsigned int testing;
	unsigned short int curLib, curComp;
	unsigned int input;


	for (j = 0; j < 8; j++){



		//IOWR_8DIRECT(euclideanAddress, 0, library[j]);
		//IOWR_8DIRECT(euclideanAddress, 8, toCompare[j]);
		//unsigned long long 64
		//unsigned short int 16
		//usleep (5000);
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
*/
