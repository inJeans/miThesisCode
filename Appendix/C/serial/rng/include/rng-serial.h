//
//  rng-serial.h
//  miThesisCode
//
//  Created by Christopher Watkins on 17/06/2015.
//
//

#ifndef __miThesisCode__rng_serial__
#define __miThesisCode__rng_serial__

#include <stdio.h>

typedef struct state
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int c;
} state;

unsigned int devrand( void );
state initrng( void );
unsigned int JKISS( state *s );
double dblrand( state *s );

#endif /* defined(__miThesisCode__rng_serial__) */
