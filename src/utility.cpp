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

#include "utility.h"
#include "constants.h"
#include "utility.h"
#include <time.h>
#include <iostream> 
#include <iomanip>
#include <sstream> 

using namespace utility;
using namespace std;

namespace utility {
long NearestInteger(double a)
{
	// returns nearest integer to a
	// 0.5 is rounded up

	if (fabs(a) > MACHINE_LARGEST_LONG)
		ThrowException("NearestInteger : argument is larger than largest long int");
		
	long n = (long) floor(a);
	if ((a - n) < 0.5)
		return n;
	else
		return n + 1;
}



bool FloatComparison(double a, double b, FloatComparisonType compareType, double tol)
{
	double difference = a - b;
	double floatCompare = 0.5 * tol * (fabs(a) + fabs(b));
	
	if ((tol <= 0.0) || (tol >= 1.0)) 
		ThrowException("FloatComparison : inappropriate tolerance");
	
	if (compareType == FLOAT_EQUALITY) {
		if (floatCompare == 0.0)
			return true;
		else
			return fabs(difference) < floatCompare;
	}
	
	if (compareType == FLOAT_GREATER_THAN) {
		return difference > floatCompare;
	}
	
	if (compareType == FLOAT_LESS_THAN) {
		return difference < -floatCompare;
	}
	
	ThrowException("FloatComparison : bad comparison type");
	return false;
}



void GetMantissaAndExponent(double x, double &mantissa, short &exponent)
{
	// this function takes the argument x and splits it into a base 10
	// mantissa and exponent
	// the mantissa is computed to lie in the range (-1, 1).

	const static double ln10 = log(10.0);

	if (x == 0.0) {
		mantissa = 0.0;
		exponent = 0;
		return;
	}

	double intpart;
	modf(log10(fabs(x)), &intpart);    
	 
	if (fabs(x) < 1.0) 
		exponent = (short) (intpart - 1.0);
	else 
		exponent = (short) (intpart);

	mantissa = x / exp(exponent * ln10);

	// this puts mantissa in the required range
	mantissa *= 0.1;
	exponent += 1;


	return;
}



double ConvertAngleToStandardRange(double angle)
{
	// angle is assumed to be in radians
	// returns angle within 0 and 2 PI
	
	if ((angle >= 0.0) && (angle <= 2.0 * PI))
		return angle;

	long n = (long) floor(fabs(angle) / (2.0 * PI));

	if (n == 0)
		return angle;

	if (angle < 0.0) 
		return angle + n * 2.0 * PI;
	else 
		return angle - n * 2.0 * PI;
}



bool TimeAndDate(short &month, short &day, short &year, short &hour, short &minute, short &sec) 
{
	// current time and date
	// month: 1 = Jan, 12 = Dec
	// day: 1 = first of month
	// year: 00 = 2000 (i.e., report last two digits of year)
	// hour: 12 = noon
	// min and seconds are the obvious values

	time_t ltime;
	time(&ltime);
	struct tm *localTime = localtime(&ltime);
	if (localTime == NULL) {
		// in this case the host machine time preceeds 01/01/70
		return false;
	}
		
	month = localTime->tm_mon + 1;
	day = localTime->tm_mday;
	year = localTime->tm_year - 100;
	hour = localTime->tm_hour;
	minute = localTime->tm_min;
	sec = localTime->tm_sec;

	return true;
}



string Date()
{
	// returns date in 1/1/01 format
	short month, year, day, hour, minute, sec;
	if (TimeAndDate(month, day, year, hour, minute, sec)) {
		string date = ConvertIntegerToString(month);
		date += "/";
		date += ConvertIntegerToString(day);
		date += "/";
	
		if (year < 10)
			date += "0";
		date += ConvertIntegerToString(year);

		return date;
	}
	else {
		return "Date unknown";
	}
}



string Time()
{
	// returns time in 21:01:01 format
	short month, year, day, hour, minute, sec;
	
	if (TimeAndDate(month, day, year, hour, minute, sec)) {
		string time;
		if (hour < 10)
			time = "0";
		time += ConvertIntegerToString(hour);
		time += ":";
	
		if (minute < 10)
			time += "0";
		time += ConvertIntegerToString(minute);
		time += ":";
	
		if (sec < 10)
			time += "0";
		time += ConvertIntegerToString(sec);

		return time;
	}
	else {
		return "Time unknown";
	}
}



void PrintElapsedTime(double seconds, TimePrintMode printMode)
{
	static const double oneMinute = 60.0;
	static const double oneHour = 60.0 * oneMinute;
	static const double oneDay = 24.0 * oneHour;
	
	if (printMode == PRINT_SECONDS) {
		cout << seconds << " seconds" << endl;
		return;
	}
	
	cout.setf(ios::fixed);
	cout << setprecision(0);
	
	if (seconds < oneMinute) {
		cout << seconds << " seconds" << endl;
		return;
	}
	
	if (seconds < oneHour) {
		double minutes = floor(seconds / oneMinute);
		double sec = seconds - oneMinute * minutes;
		
		cout << minutes << " minute";
		if (minutes > 1.5)
			cout << "s";
		
		cout << ", " << sec << " seconds" << endl;
		return;
	}
	
	if (seconds < oneDay) {
		double hours = floor(seconds / oneHour);
		double minutes = floor((seconds - oneHour * hours) / oneMinute);
		double sec = seconds - oneHour * hours - oneMinute * minutes;
		
		cout << hours << " hour";
		if (hours > 1.5)
			cout << "s";
		
		cout << ", " << minutes << " minute";
		if (minutes > 1.5)
			cout << "s";
		
		cout << ", " << sec << " seconds" << endl;
	}
	else {
		double days = floor(seconds / oneDay);
		double hours = floor((seconds - oneDay * days) / oneHour);
		double minutes = floor((seconds - oneHour * hours - oneDay * days) / oneMinute);
		double sec = seconds - oneHour * hours - oneMinute * minutes - oneDay * days;
		
		cout << days << " day";
		if (days > 1.5)
			cout << "s";
			
		cout << ", " << hours << " hour";
		if (hours > 1.5)
			cout << "s";
		
		cout << ", " << minutes << " minute";
		if (minutes > 1.5)
			cout << "s";
		
		cout << ", " << sec << " seconds" << endl;
	}
	
	cout.unsetf(ios::fixed);
	
	return;
}



string ConvertIntegerToString(long long n, bool withCommas)
{
	ostringstream stringStream;
	
	long long m = (n < 0) ? -n : n;
	stringStream << m;
	
	string s = stringStream.str();
	string tmp = s;
	
	if (withCommas) {
		short k = 0;
		for (short i = tmp.length() - 1; i > 0 ; --i) {
			++k;
			if (k % 3 == 0)
				s.insert(i, ",");
		}
	}
	
	if (n < 0)
		s = "-" + s;
	
	return s;
}



string ConvertRealToString(double x, short precision)
{
	ostringstream stringStream;
	stringStream << setprecision(precision) << x;
	return stringStream.str();
}



long ConvertStringToInteger(const string &s)
{
	// converts a string of the form '1234' to an integer
	
	if (s.size() > 9)
		ThrowException("ConvertStringToInteger : string is too long");
		
	// check for leading sign
	long sign = 1;
	long startPosition = 0;
	if (s[0] == '-') {
		sign = -1;
		startPosition = 1;	
	}
	if (s[0] == '+') {
		sign = 1;
		startPosition = 1;	
	}
		
	long value = 0;
	long m = 1;
	for (short i = s.length() - 1; i >= startPosition ; --i) {
		if (isdigit(s[i]) == false)
			ThrowException("ConvertStringToInteger : string not an integer");
		
		value += m * (((short) s[i]) - 48);
		m *= 10;
	}
	
	return sign * value;
}



bool ExtractPositiveIntegerFromString(const string &s, long &stringPosition, long &n)
{
	// extracts an integer of the form '1234' from s starting at position stringPosition
	
	if (stringPosition > s.length())
		ThrowException("ExtractIntegerFromString : bad start position");
	
	// find beginning of integer
	bool stop = false, inString = false;
	string sInt;
	while (!stop && (stringPosition < s.length())) {
		if (isdigit(s[stringPosition])) {
			sInt += s[stringPosition];
			inString = true;
			++stringPosition;
		}
		else {
			stop = inString;
			if (!stop)
				++stringPosition;
		}
	}
	
	if (inString == true) {
		n = ConvertStringToInteger(sInt);
		return true;
	}
	else {
		return false;
	}
}



void ConvertStringToIntegerArray(const std::string &s, Array<long> &a)
{
	list<long> intList;
	long stringPosition = 0;
	
	long n;
	while (stringPosition < s.length()) {
		if (ExtractPositiveIntegerFromString(s, stringPosition, n))
			intList.push_back(n);
	}
	
	a = intList;
	
	return;
}



double ConvertStringToFloat(const std::string &s)
{
	string number = s;
	string::size_type ePos = number.find('e');
	if (ePos == string::npos) 
		ePos = number.find('E');
	
	double factor = 1.0;
	
	// if 'e' or 'E' found in string compute exponent
	if (ePos != string::npos) {
		double exponent = ConvertStringToInteger(number.substr(ePos + 1));
		if (exponent > 0)
			factor = Power(10.0, (short) exponent);
		else
			factor = Power(0.1, (short) -exponent);
			
		number.erase(ePos);
	}
	
	string::size_type decimalPos = number.find('.');
	if (decimalPos != string::npos) {
		double value = ConvertStringToInteger(number.substr(0, decimalPos));
		double signValue = (value < 0) ? -1.0 : 1.0;
		number.erase(0, decimalPos + 1);
		value += signValue * ConvertStringToInteger(number) * Power(0.1, (short) number.length());
		factor *= value;
	}
	else {
		factor *= ConvertStringToInteger(number);
	}
	
	return factor;
}



void LowerCase(string &s)
{
	for (unsigned long i = 0; i < s.length(); ++i) 
		s[i] = tolower(s[i]);
	
	return;
}



void Capitalize(string &s)
{
    // capitalize first character of s which is a letter
    for (unsigned long i = 0; i < s.length(); ++i) {
        if (isalpha(s[i])) {
            s[i] = toupper(s[i]);
            return;
        }
    }
    
    return;
}



string ExtractDirectoryName(string fileName)
{
	// check if pathname is relative
	if (fileName[0] == '.') 
		ThrowException("ExtractDirectoryName : relative pathname encountered");
		
	// search backwards from end of string to find last '/'
	bool found = false;
	string directoryName = fileName;
	unsigned long i = directoryName.length() - 1;
	
	while ((!found) && (i > 0)) {
		found = (directoryName[i] == '/');
		if (!found) {
			directoryName.erase(i);
			--i;
		}
	}
	
	if (!found)
		ThrowException("ExtractDirectoryName : string " + fileName + " does not appear to contain a directory");
		
	
	return directoryName;
}



bool IsAFullPathName(const std::string &fileName)
{
	return fileName[0] == '/';
}



void OpenInputFile(const string &fileName, ifstream &file)
{
    file.open(fileName.c_str());
    
	if (file.good() == false) 
		ThrowException("OpenInputFile : can't find " + fileName);
        
    return;
}



void OpenOutputFile(const string &fileName, ofstream &file)
{
    file.open(fileName.c_str());
    
	if (file.good() == false) 
		ThrowException("OpenOutputFile : couldn't open " + fileName);
        
    return;
}



double BigFactorial(long n)
{
	if (n < 1)
		ThrowException("Factorial : n less than 1");
	
	double logLargest = log(MACHINE_LARGEST_DOUBLE);
	
	double factorial = 1.0;
	for (long i = 1; i <= n; ++i) {
		double x = (double) i;
		
		// check for overflow
		if (log(x) + log(factorial) > logLargest)
			ThrowException("BigFactorial : overflow");
		
		factorial *= x;
	}
		
	return factorial;
}



double BigCombination(long numObjects, long numPicked)
{
	// returns number of ways to pick numPicked objects
	// from numObjects in any order and with no repetition
	if ((numPicked < 0) || (numObjects < 0) || (numPicked > numObjects))
		ThrowException("Combination : bad input");
		
	if ((numPicked == 0) || (numPicked == numObjects))
		return 1;
		
	double value = 1.0;
	
	for (long i = 0; i < numPicked; ++i)
		value *= ((double) (numObjects - i)) / (i + 1.0);
	
	return value;
}



double FloatingPointMachinePrecision()
{
	int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
	double eps, epsneg, xmin, xmax;
	
	machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &eps, &epsneg, &xmin, &xmax);
	
	return eps;
}



double MachineLargestDouble()
{
	int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
	double eps, epsneg, xmin, xmax;
	
	machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &eps, &epsneg, &xmin, &xmax);
	
	return xmax;
}



double MachineSmallestDouble(void)
{
	int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
	double eps, epsneg, xmin, xmax;
	
	machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, &eps, &epsneg, &xmin, &xmax);
	
	return xmin;
}



long MachineLargestLong()
{
    short s = sizeof(long);
    double x = Power(2.0, 8.0 * s - 1.0);
    return (long) (x - 1.0);
}



short MachineLargestShort()
{
    short s = sizeof(short);
    double x = Power(2.0, 8.0 * s - 1.0);
    return (short) (x - 1.0);
}



void ThrowException(const string &message)
{
	throw message;
	return;
}



void HandleException(exception stdExcep)
{
	string message = stdExcep.what();
	message = "Standard exception : " + message;
	cout << message << endl;
    
	return;
}



void HandleException(string message)
{
	cout << "Project exception : " + message << endl;
	return;
}
}
