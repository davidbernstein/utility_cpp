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

#ifndef _clock_h_
#define _clock_h_

#include <time.h>
#include <string>
#include <iostream>

#include "utility.h"

namespace utility {
	class Clock {
    public:
		// Constructors
		Clock(void);
        
		// Destructor
        ~Clock(void) { };
        
        void Start(void);
		double Stop(void);
		double StopAndPrintTime(std::string prefix = "");
		void SetPrintMode(TimePrintMode mode);
        
    private:
    	clock_t mStartTime;
    	bool mStarted;
		TimePrintMode mPrintMode;
	};
	
	
	
	inline Clock::Clock(void)
	{
		mStarted = false;
		mPrintMode = PRINT_HOURS_MINUTES_SECONDS;
		
		return;
	}
	
	


	inline void Clock::Start()
	{
		mStartTime = clock();
		mStarted = true;

		return;
	}
	


	inline double Clock::Stop()
	{
		if (mStarted == false)
			return 0.0;
			
		clock_t endTime = clock();
		mStarted = false;

		return ((double) (endTime - mStartTime)) / ((double) CLOCKS_PER_SEC);
	}



	inline double Clock::StopAndPrintTime(std::string prefix)
	{
		if (mStarted == false)
			return 0.0;
			
		double t = Stop();
	
		if (prefix != "")
			std::cout << prefix << " ";
	
		PrintElapsedTime(t, mPrintMode);
	
		return t;
	}
	
	
	inline void Clock::SetPrintMode(TimePrintMode mode)
	{
		mPrintMode = mode;
		return;
	}
}


#endif // _clock_h_



