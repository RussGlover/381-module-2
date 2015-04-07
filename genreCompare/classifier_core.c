#include "classifier_core.h"

int main()
{
	unsigned int data = 15000;
	printf("Resetting core \n");
	//Reset core
	IOWR_32DIRECT(classifier_core_base,60,data);
	printf("Core reset \n");

	printf("Write bin 0/1 of test data \n");
	//Write bin 0/1 of test data
	IOWR_32DIRECT(classifier_core_base,0,data);

	printf("Write bin 2/3 of test data \n");
	//Write bin 2/3 of test data
	IOWR_32DIRECT(classifier_core_base,4,data);

	printf("Write bin 4/5 of test data \n");
	//Write bin 4/5 of test data
	IOWR_32DIRECT(classifier_core_base,8,data);

	printf("Write bin 6/7 of test data \n");
	//Write bin 6/7 of test data
	IOWR_32DIRECT(classifier_core_base,12,data);

	int i;

	for( i = 0; i < 8; i++)
	{
		printf("Writing bin %i \n", i);
		//Write bin 0 of library data
		IOWR_32DIRECT(classifier_core_base,16,encode(i,0));

		//Write bin 1 of library data
		IOWR_32DIRECT(classifier_core_base,20,encode(i,0));

		//Write bin 2 of library data
		IOWR_32DIRECT(classifier_core_base,24,encode(i,0));

		//Write bin 3 of library data
		IOWR_32DIRECT(classifier_core_base,28,encode(i,0));

		//Write bin 4 of library data
		IOWR_32DIRECT(classifier_core_base,32,encode(i,0));

		//Write bin 5 of library data
		IOWR_32DIRECT(classifier_core_base,36,encode(i,0));

		//Write bin 6 of library data
		IOWR_32DIRECT(classifier_core_base,40,encode(i,0));

		//Write bin 7 of library data
		IOWR_32DIRECT(classifier_core_base,44,encode(i,0));
	}

	//Start
	printf("Starting \n");
	IOWR_32DIRECT(classifier_core_base,36,0);

	printf("Waiting for classifiers to finish \n");
	while( (IORD_32DIRECT(classifier_core_base,0) != 255) )
		{
			printf("Done status is: %i \n", IORD_32DIRECT(classifier_core_base,0));
		}
	printf("Classifiers finished \n");

	printf("Result is: %i \n", IORD_32DIRECT(classifier_core_base,4));

}

unsigned int encode(short int address, unsigned short int value)
{
	unsigned int temp = 0;
	temp = temp | address;
	temp <<= 16;
	temp = temp | value;
	return temp;
}
