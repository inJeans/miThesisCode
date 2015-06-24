//
//  generateInitalDistribution.c
//  miThesisCode
//
//  Created by Christopher Watkins on 19/05/2015.
//
//

double maxGridWidth = 0.01;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "generateInitialDistribution.h"
#include "definePhysicalConstants.h"
#include "defineSimulationParameters.h"

void generateInitialDist(double3 *pos,
                         double3 *vel,
                         int      numberOfAtoms,
                         double   initialTemp );

double3 getRandomVelocity( double Temp );

double3 selectAtomInThermalDistribution( double Temp );

double3 getGaussianPoint(double mean,
                         double std);

double2 randn(double mu,
              double sigma);

int main(int argc, const char * argv[])
{
    double3 pos[NUM_ATOMS] = { 0., 0., 0. };
    double3 vel[NUM_ATOMS] = { 0., 0., 0. };
    
    generateInitialDist(pos,
                        vel,
                        NUM_ATOMS,
                        initialTemp );
	
//    testDist();
    
    FILE *posFile;
    FILE *velFile;
    
    if ( ( posFile = fopen("pos.bin", "wb") ) == NULL )
	{
		printf("Unable to create pos.bin");
		exit(-1);
	}
    if ( ( velFile = fopen("vel.bin", "wb") ) == NULL )
	{
		printf("Unable to create vel.bin");
		exit(-1);
	}
	
    fwrite(pos, sizeof(double3), NUM_ATOMS, posFile);
    fwrite(vel, sizeof(double3), NUM_ATOMS, velFile);
	
    fclose(posFile);
    fclose(velFile);
	
    return 0;
}

// Kernel to generate the initial distribution
void generateInitialDist(double3 *pos,
                         double3 *vel,
                         int      numberOfAtoms,
                         double   initialTemp )
{
#pragma omp parallel for
    for (int atom = 0;
         atom < numberOfAtoms;
         atom++)
    {
        srand((int)time(NULL) ^ omp_get_thread_num());
        
        pos[atom] = selectAtomInThermalDistribution( initialTemp );
        
        vel[atom] = getRandomVelocity( initialTemp );
    }
    
    return;
}

double3 getRandomVelocity( double Temp )
{
    double3 vel = { 0., 0., 0. };
    
    double V = sqrt( kB*Temp / mass);
    
    vel = getGaussianPoint( 0., V );
    
    return vel;
}

double3 selectAtomInThermalDistribution( double Temp )
{
    double3 r   = { 0., 0., 0. };
    double3 pos = { 0., 0., 0. };
    
    bool noAtomSelected = true;
    while (noAtomSelected) {
        
        double2 r1 = randn(0.,
                           1.);
        double2 r2 = randn(0.,
                           1.);
        
        double3 r = { r1.x, r1.y, r2.x };
        r = r * maxGridWidth / 3.;
        
        double  magB = norm( B( r ) );
        
        double U = 0.5 * (magB - B0) * gs * muB;
        
        double Pr = exp( -U / kB / Temp );
        
        if ( ((double) rand () / RAND_MAX) < Pr) {
            pos = r;
            noAtomSelected = false;
        }
    }
    
    return pos;
}

double3 getGaussianPoint(double mean,
                         double std)
{
    double2 r1 = randn(mean,
                       std);
    double2 r2 = randn(mean,
                       std);
    
    double3 point = { r1.x, r1.y, r2.x };
    
    return point;
}

double2 randn(double mu,
              double sigma)
{
    double U1, U2, W, mult;
    double X1, X2;
    
    do
    {
        U1 = -1 + ((double) rand () / RAND_MAX) * 2;
        U2 = -1 + ((double) rand () / RAND_MAX) * 2;
        W = pow (U1, 2) + pow (U2, 2);
    }
    while (W >= 1 || W == 0);
    
    mult = sqrt ((-2 * log (W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;
    
    double2 r = {mu + sigma * (double) X1,
                 mu + sigma * (double) X2 };
    
    return r;
}