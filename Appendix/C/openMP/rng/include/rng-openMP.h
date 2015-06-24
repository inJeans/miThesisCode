//
//  rng-openMP.h
//  miThesisCode
//
//  Created by Christopher Watkins on 24/06/2015.
//
//

#ifndef __miThesisCode__rng_openMP__
#define __miThesisCode__rng_openMP__

#include <stdio.h>
#include <omp.h>

typedef struct state
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int c;
} state;

unsigned int devrand( void );
state initrng( void );
void parallelinitrng(state *states,
					 int numberOfThreads);

unsigned int JKISS( state *s );
double dblrand( state *s );
void parallelrand(double *randarray,
				  int numberOfThreads,
				  state *states );

#endif /* defined(__miThesisCode__rng_openMP__) */
