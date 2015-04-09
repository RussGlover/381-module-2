#include "classifier_core.h"

int main()
{
	unsigned short int data = 90;
	unsigned short int data2 = 87;
	int samples = 3;
	
	printf("Resetting core \n");
	//Reset core
	IOWR_32DIRECT(classifier_core_base,0,0);
	printf("Core reset \n");
	
	printf("Writing in test data \n");
	IOWR_32DIRECT(classifier_core_base,8,data);


	int i;

	for( i = 0; i < samples; i++)
	{
		printf("Writing bin %i \n", i);
		//Write bin 0 of library data
		IOWR_32DIRECT(classifier_core_base,4,encode(i, data2));
	}

	
	printf("Classifiers finished \n");
	for(i = 0; i < samples ; i++)
	{
		printf("Result is: %i \n", IORD_32DIRECT(classifier_core_base,i));
	}
	return 0;

}


unsigned int encode(short int address, unsigned short int value)
{
	unsigned int temp = 0;
	temp = temp | address;
	temp <<= 16;
	temp = temp | value;
	return temp;
}
