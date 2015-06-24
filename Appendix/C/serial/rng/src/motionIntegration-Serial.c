//
//  motionIntegration-Serial.c
//  miThesisCode
//
//  Created by Christopher Watkins on 17/05/2015.
//
//

#include "motionIntegration-Serial.h"
#include "definePhysicalConstants.h"
#include "defineSimulationParameters.h"
#include "magneticField.h"

#define LOOPS_PER_PRINT 1000
#define MAX_ITER 1000

void readFiles(double3 *pos,
               double3 *vel,
               int numberOfAtoms);

void moveParticles(double3 *pos,
                   double3 *vel,
                   double3 *acc,
                   double dt,
                   int numberOfAtoms);

void velocityVerletUpdate(double3 *pos,
                          double3 *vel,
                          double3 *acc,
                          double dt);

void symplecticEulerUpdate(double3 *pos,
                           double3 *vel,
                           double3 *acc,
                           double dt);

double3 updateVel(double3 vel,
                  double3 acc,
                  double dt);

double3 updatePos(double3 pos,
                  double3 vel,
                  double dt);

double3 updateAcc(double3 pos);

int main(int argc, const char * argv[])
{
    double3 pos[NUM_ATOMS] = { 0., 0., 0. };
    double3 vel[NUM_ATOMS] = { 0., 0., 0. };
    double3 acc[NUM_ATOMS] = { 0., 0., 0. };
    
    readFiles(pos,
              vel,
              NUM_ATOMS);
    
    double dt = 1.e-6;
    
    for (int i=0; i<MAX_ITER; i++) {
        moveParticles(pos,
                      vel,
                      acc,
                      dt,
                      NUM_ATOMS);
    }
    
//    testResults();
    
    return 0;
}

void readFiles(double3 *pos,
               double3 *vel,
               int numberOfAtoms)
{
    FILE *posFile;
    FILE *velFile;
    
    posFile = fopen("pos.bin", "rb");
    velFile = fopen("vel.bin", "rb");
    
    fread(pos, sizeof(double3), NUM_ATOMS, posFile);
    fread(vel, sizeof(double3), NUM_ATOMS, velFile);
    
    fclose(posFile);
    fclose(velFile);
    
    return;
}

void moveParticles(double3 *pos,
                   double3 *vel,
                   double3 *acc,
                   double dt,
                   int numberOfAtoms)
{
    #pragma omp parallel for
    for (int atom = 0; atom < NUM_ATOMS; atom++)
    {
        for (int i=0; i<LOOPS_PER_PRINT; i++) {
            velocityVerletUpdate(pos,
                                 vel,
                                 acc,
                                 dt);
        }
    }
    
    return;
    
}

void velocityVerletUpdate(double3 *pos,
                          double3 *vel,
                          double3 *acc,
                          double dt)
{
    vel[0] = updateVel(vel[0],
                       acc[0],
                       0.5*dt);
    pos[0] = updatePos(pos[0],
                       vel[0],
                       dt);
    acc[0] = updateAcc(pos[0]);
    vel[0] = updateVel(vel[0],
                       acc[0],
                       0.5*dt);
    
    return;
}

void symplecticEulerUpdate(double3 *pos,
                           double3 *vel,
                           double3 *acc,
                           double dt)
{
    acc[0] = updateAcc(pos[0]);
    vel[0] = updateVel(vel[0],
                       acc[0],
                       dt);
    pos[0] = updatePos(pos[0],
                       vel[0],
                       dt);
}

double3 updateVel(double3 vel,
                  double3 acc,
                  double dt)
{
    return vel + acc * dt;
}

double3 updatePos(double3 pos,
                  double3 vel,
                  double dt)
{
    return pos + vel * dt;
}

double3 updateAcc(double3 pos)
{
    
    return -0.5 * gs * muB * dabsB(pos) / mass;
}