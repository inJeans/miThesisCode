//
//  vectorTypes.h
//  miThesisCode
//
//  Created by Christopher Watkins on 25/05/2015.
//
//

#ifndef miThesisCode_vectorTypes_h
#define miThesisCode_vectorTypes_h

#include <math.h>

typedef struct double3
{
    double x, y, z;
} double3;

typedef struct double2
{
    double x, y;
} double2;

static double3 operator* ( double3 a, double b )
{
    double3 ab = { a.x*b, a.y*b, a.z*b };
    return ab;
}

static double3 operator* ( double a, double3 b )
{
    double3 ab = { a*b.x, a*b.y, a*b.z };
    return ab;
}

static double3 operator/ ( double3 a, double b )
{
    double3 aonb = { a.x/b, a.y/b, a.z/b };
    return aonb;
}

static double3 operator+ ( double3 a, double3 b )
{
    double3 ab = { a.x*b.x, a.y*b.y, a.z*b.z };
    return ab;
}

static double norm( double3 a )
{
    return sqrt( a.x*a.x + a.y*a.y + a.z*a.z );
}

static double3 normal( double3 a )
{
    double n = norm( a );
    double3 an = { a.x/n, a.y/n, a.z/n };
    return an;
}

#endif
