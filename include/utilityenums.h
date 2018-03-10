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

#ifndef _utilityenums_h_
#define _utilityenums_h_

//#include "utility.h"

namespace utility {
	enum FloatComparisonType{FLOAT_EQUALITY, FLOAT_GREATER_THAN, FLOAT_LESS_THAN};
    
	enum RandomNumberGeneratorType{RAN2, RAN3, LSFR258};
	
	enum TimePrintMode{PRINT_SECONDS, PRINT_HOURS_MINUTES_SECONDS};
    
    enum UnitsType{NO_UNITS, DIMENSIONLESS,
    
                   // length 
                   METERS, CENTIMETERS, MILLIMETERS, MICRONS, NANOMETERS,
        
                   // time
                   SECONDS, HOURS};
    
}

#endif // _utilityenums_h_
