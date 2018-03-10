/*
 * Copyright (C) 2004-2018 David Bernstein <david.h.bernstein@gmail.com>
 *
 * This file is part of utility_cpp.
 *
 * utility_cpp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * utility_cpp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with utility_cpp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "complexnumber.h"
#include <math.h>

using namespace std;
using namespace utility;

double ComplexNumber::Phase(void) const
{
    // return value is between 0 and 2 pi
    
    // phase is between -pi and pi
    double phase;
    phase = atan2(mImaginary, mReal);
    
    if (phase >= 0.0) {
        return phase;
    }
    else {
        return phase + 2.0 * PI;
    }
}



void ComplexNumber::Print(void) const
{
    cout << mReal;
    
    if (mImaginary == 0.0) {
        return;
    }
    
    if (mImaginary < 0.0) {
        cout << " - i * ";
    }
    else {
        cout << " + i * ";
    }
    
    cout << fabs(mImaginary);
    
	return;
}
