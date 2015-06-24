//
//  magneticField.c
//  miThesisCode
//
//  Created by Christopher Watkins on 25/05/2015.
//
//

//#include <math.h>

#include "magneticField.h"

double dBdz = 2.5;
double B0   = 0.;

double3 B( double3 pos )
{
    double3 B = { 0., 0., 0. };
    
    B.x =  0.5 * dBdz * pos.x;
    B.y =  0.5 * dBdz * pos.y;
    B.z = -1.0 * dBdz * pos.z;
    
    return B;
}

double3 dabsB(double3 pos)
{
    double3 dabsB = { 0., 0., 0. };
    
    /////////////////////////////////////////
    // Make changes to magnetic field      //
    // derivative here                     //
    /////////////////////////////////////////
    
    dabsB.x = 0.5 * dBdz * pos.x / sqrt( pos.x*pos.x + pos.y*pos.y + 4.*pos.z*pos.z );
    dabsB.y = 0.5 * dBdz * pos.y / sqrt( pos.x*pos.x + pos.y*pos.y + 4.*pos.z*pos.z );
    dabsB.z = 2.0 * dBdz * pos.z / sqrt( pos.x*pos.x + pos.y*pos.y + 4.*pos.z*pos.z );
    
    return dabsB;
}
