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

#ifndef _units_h_
#define _units_h_

#include "utility.h"
#include "constants.h"

namespace utility {
	class Units {
    public:
		Units(void);
        ~Units(void) { };
		        
        void SetTimeUnits(std::string timeUnits);
		void SetLengthUnits(std::string lengthUnits);
        
    private:
		void SetTimeUnits(UnitsType timeUnits);
		void SetLengthUnits(UnitsType lengthUnits);
        UnitsType GetUnitsType(const std::string &name);
        
    private:
        // conversion of length units to meters
        double mConversionToMeters;
		
		// conversion of time units to seconds
		double mConversionToSeconds;
	};
    
    
    
    inline Units::Units()
    {
        mConversionToMeters = -1.0;
        mConversionToSeconds = -1.0;
        
        return;
    }
}


#endif // _units_h_




