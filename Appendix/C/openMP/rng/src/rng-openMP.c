//
//  rng-openMP.c
//  miThesisCode
//
//  Created by Christopher Watkins on 24/06/2015.
//
//

#include <stdlib.h>
#include <omp.h>

#include "rng-openMP.h"

unsigned int devrand( void )
{
	FILE *fn;
	unsigned int r;
	
	fn = fopen("/dev/urandom", "r");
	
	if (fn == NULL)
	{
		printf("Unable to read from /dev/urandom\n");
		exit(-1);
	}
	
	if (fread(&r, sizeof(unsigned int), 1, fn) != 1)
	{
		exit(-1);
	}
	
	fclose(fn);
	
	return r;
}

state initrng( void )
{
	state s;
	
	s.x = devrand();
	while (!(s.y = devrand())); /* y must not be zero */
	s.z = devrand();
	
	s.c = devrand() % 69876908 + 1; /* NOTE: offset c by 1 to avoid z=c=0 */
	
	return s;
}

void parallelinitrng(state *states,
					 int numberOfThreads)
{
#pragma omp parallel for
	for (int s = 0;
		 s < numberOfThreads;
		 s++)
	{
		states[s] = initrng( );
	}
	return;
}

unsigned int JKISS( state *s )
{
	unsigned long long t;
	
	s->x = 314527869 * s->x + 1234567;
	s->y ^= s->y << 5; s->y ^= s->y >> 7; s->y ^= s->y << 22;
	t = 4294584393ULL * s->z + s->c; s->c = t >> 32; s->z = t;
	
	return s->x + s->y + s->z;
}

double dblrand( state *s )
{
	double x;
	unsigned int a, b;
	
	a = JKISS( s ) >> 6; /* Upper 26 bits */
	b = JKISS( s ) >> 5; /* Upper 27 bits */
	x = (a * 134217728.0 + b) / 9007199254740992.0;
	
	return x;
}

void parallelrand(double *randarray,
				  int numberOfThreads,
				  state *states )
{
#pragma omp parallel for
	for (int r = 0;
		 r < numberOfThreads;
		 r++)
	{
        int t = omp_get_thread_num();
		randarray[t*1+r] = dblrand( &states[r] );
	}
	
	return;
}