//
//  magneticField.h
//  miThesisCode
//
//  Created by Christopher Watkins on 25/05/2015.
//
//

#ifndef __miThesisCode__magneticField__
#define __miThesisCode__magneticField__

#include <stdio.h>
#include "vectorTypes.h"

extern double dBdz;
extern double B0;

double3 B( double3 pos );
double3 dabsB(double3 pos);

#endif /* defined(__miThesisCode__magneticField__) */
