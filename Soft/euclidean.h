/*
 * euclidean.h
 *
 *  Created on: 2015-03-19
 *      Author: Aaron
 */

#ifndef EUCLIDEAN_H_
#define EUCLIDEAN_H_

#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

int euclideanS(unsigned short int library, unsigned short int toCompare);
unsigned long long euclideanSingle(unsigned short int library[8], unsigned short int toCompare[8]);
unsigned long long euclideanCalc(unsigned short int library[8], unsigned short int toCompare[8]);

#endif /* EUCLIDEAN_H_ */
