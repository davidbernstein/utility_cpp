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

#include "units.h"
#include "utility.h"

using namespace utility;
using namespace std;

void Units::SetTimeUnits(string timeUnits)
{
    SetTimeUnits(GetUnitsType(timeUnits));
    return;
}



void Units::SetLengthUnits(string lengthUnits)
{
    SetLengthUnits(GetUnitsType(lengthUnits));
    return;
}



void Units::SetLengthUnits(UnitsType lengthUnits)
{
    switch (lengthUnits) {
        case METERS:
            mConversionToMeters = 1.0;
            break;
            
        case CENTIMETERS:
            mConversionToMeters = CENTIMETERS_TO_METERS;
            break;
            
        case MILLIMETERS:
            mConversionToMeters = MILLIMETERS_TO_METERS;
            break;
            
        case MICRONS:
            mConversionToMeters = MICRONS_TO_METERS;
            break;
            
        default:
            ThrowException("Simulation::SetLengthUnits : bad units type");
            break;
    }
    
    return;
}



void Units::SetTimeUnits(UnitsType timeUnits)
{
    switch (timeUnits) {
        case SECONDS:
            mConversionToSeconds = 1.0;
            break;
		
		case HOURS:
			mConversionToSeconds = HOURS_TO_SECONDS;
			break;
			
        default:
            ThrowException("Simulation::SetTimeUnits : bad units type");
            break;
    }
    
    return;
}



UnitsType Units::GetUnitsType(const string &name)
{
	string tmp = name;
	LowerCase(tmp);
	
	if (tmp == "meters")
		return METERS;
    
	if (tmp == "centimeters")
		return CENTIMETERS;
    
	if (tmp == "millimeters")
		return MILLIMETERS;
	
	if (tmp == "microns")
		return MICRONS;
    
	if (tmp == "seconds")
		return SECONDS;
    
	if (tmp == "hours")
		return HOURS;
    
	ThrowException("GetUnitsType : bad input string : " + name);
    
	return NO_UNITS;
}
