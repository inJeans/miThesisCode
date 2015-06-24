//
//  rngTest-serial.c
//  miThesisCode
//
//  Created by Christopher Watkins on 17/06/2015.
//
//
#include <stdlib.h>
#include <time.h>

extern "C"
{
#include "TestU01.h"
#include "bbattery.h"
}
	
#include "rngTest-serial.h"
#include "rng-serial.h"

//51320000
#define NUM_RN 51320000

int main(int argc, const char * argv[])
{
	state rngstate;
	
	rngstate = initrng( );
	
	char rndfilename[] = "rndnum.txt";
	
	FILE *rndfileptr;
	
	rndfileptr = fopen(rndfilename, "w+");
	
    clock_t begin, end;
    double time_spent;
    
    begin = clock();
    
	for (int i=0; i < NUM_RN; i++) {
		fprintf( rndfileptr, "%.15f ",  dblrand( &rngstate ) );
	}
	
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
	fclose(rndfileptr);
	
    printf("Time spent generating file = %fs\n", time_spent);
    
	bbattery_SmallCrushFile( rndfilename );
	
	return 0;
}
