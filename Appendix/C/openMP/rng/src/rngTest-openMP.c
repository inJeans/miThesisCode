//
//  rngTest-openMP.c
//  miThesisCode
//
//  Created by Christopher Watkins on 24/06/2015.
//
//

#include <stdlib.h>
#include <time.h>

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
	double randarray[BATCH_SIZE*10] = { 0. };
	
	parallelinitrng(rngstates,
					BATCH_SIZE );
	
	char rndfilename[] = "rndnum.txt";
	
	FILE *rndfileptr;
	
	rndfileptr = fopen(rndfilename, "w+");
	
	int num_loops = NUM_RN / BATCH_SIZE / 1 + 1;
    
    clock_t begin, end;
    double time_spent;
    
    begin = clock();
	for (int l=0; l<num_loops; l++) {
		parallelrand(randarray,
					 BATCH_SIZE,
				     rngstates );
		
		for (int r=0; r < BATCH_SIZE*1; r++) {
			fprintf( rndfileptr, "%.15f ",  randarray[r] );
		}
	}
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	fclose(rndfileptr);
	
    printf("Time spent generating file = %fs\n\n", time_spent);
    
//	bbattery_SmallCrushFile( rndfilename );
	
	return 0;
}