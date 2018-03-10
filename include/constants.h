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

#ifndef _constants_h_
#define _constants_h_

#include <math.h>
#include "utility.h"
#include "utility.h"

namespace utility {
	// numerical constants
	const double PI = 4.0 * atan(1.0);
	const double SQRT_TWO = sqrt(2.0);
	const double SQRT_THREE = sqrt(3.0);
	
	// machine parameters
//	const double MACHINE_PRECISION_DOUBLE = FloatingPointMachinePrecision();
//	const double MACHINE_LARGEST_DOUBLE = MachineLargestDouble();
//	const double MACHINE_SMALLEST_DOUBLE = MachineSmallestDouble();
//	const double FLOAT_COMPARE_TOL = sqrt(MACHINE_PRECISION_DOUBLE);
//	const long MACHINE_LARGEST_LONG = MachineLargestLong();
//    const short MACHINE_LARGEST_SHORT = MachineLargestShort();
	
	// other defaults
	//const short DEFAULT_REAL_TO_STRING_PRECISION = 15;
	
    // length unit conversion factors 
	// how these work:
	// if you have X centimeters and you want to convert it to meters
	// then multiply X by CENTIMETERS_TO_METERS
	const double CENTIMETERS_TO_METERS = 1.0E-02;
	const double MILLIMETERS_TO_METERS = 1.0E-03;
	const double MICRONS_TO_METERS = 1.0E-06;
	
	// time unit conversion factors
	const double HOURS_TO_SECONDS = 3600.0;
}

#endif // _constants_h_
