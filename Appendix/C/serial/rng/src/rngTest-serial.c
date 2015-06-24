//
//  rngTest-serial.c
//  miThesisCode
//
//  Created by Christopher Watkins on 17/06/2015.
//
//
#include <stdlib.h>

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
	
	for (int i=0; i < NUM_RN; i++) {
		fprintf( rndfileptr, "%.15f ",  dblrand( &rngstate ) );
	}
	
	fclose(rndfileptr);
	
	bbattery_SmallCrushFile( rndfilename );
	
	return 0;
}
