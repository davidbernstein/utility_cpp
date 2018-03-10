#ifndef _utility_h_
#define _utility_h_

#include "utility.h"
#include "utilityenums.h"
#include "array.h"

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

#include <math.h>
#include <string>
#include <list>
#include <vector>
#include <fstream>

#include "utilityenums.h"

namespace utility {
	// floating point utilities
	void GetMantissaAndExponent(double x, double &mantissa, short &exponent);
	bool FloatComparison(double a, double b, FloatComparisonType comparisonType, double tol);
	double Power(double base, double exponent);
	double Power(double base, short exponent);
	long NearestInteger(double a);
	double ConvertAngleToStandardRange(double angle);
	
	// integers 
	long SmallFactorial(short n);
	double BigFactorial(long n);
	double BigCombination(long numObjects, long numPicked);
	
	// strings
	std::string ConvertIntegerToString(long long n, bool withCommas = false);
	std::string ConvertRealToString(double x, short precision = 15);	
	long ConvertStringToInteger(const std::string &s);
	bool ExtractPositiveIntegerFromString(const std::string &s, long &stringPosition, long &n);
	double ConvertStringToFloat(const std::string &s);
	void LowerCase(std::string &s);
    void Capitalize(std::string &s);
    //void ConvertStringToIntegerArray(const std::string &s, Array<long> &a);
	std::string ExtractDirectoryName(std::string fileName);
	bool IsAFullPathName(const std::string &fileName);
    
    // file IO
    void OpenInputFile(const std::string &fileName, std::ifstream &file);
	void OpenOutputFile(const std::string &fileName, std::ofstream &file);
	
	// time and date
	bool TimeAndDate(short &month, short &day, short &year, short &hour, short &minute, short &sec);
	std::string Date(void);
	std::string Time(void);
	void PrintElapsedTime(double seconds, TimePrintMode printMode = PRINT_HOURS_MINUTES_SECONDS);

	// STL vectors
	template <class T>
	void ResizeVector(std::vector<T> &v, long n);
	
	// machine characteristics
	double FloatingPointMachinePrecision(void);
	double MachineLargestDouble(void);
	double MachineSmallestDouble(void);
    long MachineLargestLong(void);
    short MachineLargestShort(void);
    
    // debugging
    //template <class T>
    //void InspectArray(Array<T> &array);
    
    template <class T>
    void InspectList(std::list<T> &l);
	
  	// exception handling
	void ThrowException(const std::string &message);
  	void HandleException(std::string message);
	void HandleException(std::exception stdExcep);
    
	// numerical recipes
	void machar(int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep,
				int *iexp, int *minexp, int *maxexp, double *eps, double *epsneg,
				double *xmin, double *xmax);
}


namespace utility {
	inline double Power(double base, short exponent)
	{
		if (base == 0)
			return 0.0;
	
		if (exponent == 0)
			return 1.0;
			
		double tmp = base;
		
		switch (abs(exponent)) {
		case 1:
			tmp = base;
			break;
			
		case 2:
			tmp = base * base;
			break;
		
		case 3:
			tmp = base * base * base;
			break;
			
		default:
			for (short i = 0; i < exponent - 1; ++i)
				tmp *= base;
		}
		
		if (exponent < 0)
			return 1.0 / tmp;
		else
			return tmp;
	}



	inline double Power(double base, double exponent)
	{
		if (base < 0.0)
			ThrowException("Power : base is negative");
		
		if (base == 0.0)
			return 0.0;

		return exp(exponent * log(base));
	}
	


	inline long SmallFactorial(short n)
	{
		static long value[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
	
		if (n < 0)
			ThrowException("SmallFactorial : n less than 0");
	
		if (n > 12)
			ThrowException("SmallFactorial : n greater than 12, use BigFactorial");
		
		return value[n];
	}



	template <class T>
	void ResizeVector(std::vector<T> &v, long n)
	{
		// this function resizes v so that
		// v.capacity = v.size() = n
		// v is erased in the process
		std::vector<T> tmp(n);
		v.swap(tmp);
		return;
	}
    
    
    
//    template <class T>
//    void InspectArray(Array<T> &array)
//    {
//        T dum;
//        for (long i = 0; i < array.Size(); ++i) {
//            dum = array[i];
//        }
//
//        return;
//    }
    
    
    
    template <class T>
    void InspectList(std::list<T> &l)
    {
        T dum;
        typename std::list<T>::iterator iL;
        for (iL = l.begin(); iL != l.end(); ++iL) {
            dum = *iL;
        }
        
        return;
    }
}

#endif // _utility_h_
