//
//  rngTest-openMP.c
//  miThesisCode
//
//  Created by Christopher Watkins on 24/06/2015.
//
//

#include <stdlib.h>

extern "C"
{
#include "TestU01.h"
#include "bbattery.h"
}

#include "rngTest-openMP.h"
#include "rng-openMP.h"

//51320000
#define NUM_RN 51320000
#define BATCH_SIZE 1000

int main(int argc, const char * argv[])
{
	state  rngstates[BATCH_SIZE];
	double randarray[BATCH_SIZE] = { 0. };
	
	parallelinitrng(rngstates,
					BATCH_SIZE );
	
	char rndfilename[] = "rndnum.txt";
	
	FILE *rndfileptr;
	
	rndfileptr = fopen(rndfilename, "w+");
	
	int num_loops = NUM_RN / BATCH_SIZE + 1;
	for (int l=0; l<num_loops; l++) {
		parallelrand(randarray,
					 BATCH_SIZE,
				     rngstates );
		
		for (int r=0; r < BATCH_SIZE; r++) {
			fprintf( rndfileptr, "%.15f ",  randarray[r] );
		}
	}
	
	fclose(rndfileptr);
	
	bbattery_SmallCrushFile( rndfilename );
	
	return 0;
}