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

#include "randomnumbergenerator.h"
#include "utility.h"
#include "constants.h"

#include <iostream>

using namespace utility;
using namespace std;
	
RandomNumberGenerator::RandomNumberGenerator()
{
	mSeed = -1;
    mNumCalls = 0;
    mGeneratorType = RAN2;
        
    mIdum = mSeed;
        
    // initialize
    Reset(mSeed);
        
	return;
}


	
void RandomNumberGenerator::Reset()
{
	Reset(mSeed - 1);
	return;
}
	
	
	
void RandomNumberGenerator::Reset(long seed)
{
	if (seed > -1)
    	ThrowException("RandomNumberGenerator::Reset : seed must be negative");
            
	mSeed = seed;
    mNumCalls = 0;
        
    mIdum = mSeed;
        
    // initialize
    switch (mGeneratorType) {
        case RAN2:
            Random01();
            break;
            
        case RAN3:
            Random01();
            break;
        
		case LSFR258:
			Lsfr258();
			break;

        default:
            ThrowException("Reset : RANDOM_NUMBER_GENERATOR not set");
            break;
	}
    
        
    return;
}
    
    
    
void RandomNumberGenerator::Reset(long seed, RandomNumberGeneratorType type)
{
	mGeneratorType = type;
	Reset(seed);
        
    return;
}
    
  
    
double RandomNumberGenerator::RandomNumber(double lowerLimit, double upperLimit)
{
	// returns a random number between lowerLimit and upperLimit inclusive
	
	double range = upperLimit - lowerLimit;
	if (range < 0.0)
		ThrowException("RandomNumber::bad limits");
	
	if (range == 0.0)
		return lowerLimit;
    
	double between01 = Random01();
	
	return between01 * range + lowerLimit;
}



long RandomNumberGenerator::RandomInteger(long lowerLimit, long upperLimit)
{				
	return NearestInteger(RandomNumber((double) lowerLimit, (double) upperLimit));
}



long RandomNumberGenerator::FloorOrCeiling(double posNumber)
{
	if (posNumber < 0.0)
		ThrowException("RandomNumberGenerator::FloorOrCeiling : negative input");
	
	double intPart;
	double frac = modf(posNumber, &intPart);
	
	if (Random01() > frac)
		return (long) intPart;
	else
		return (long) intPart + 1;
}



void RandomNumberGenerator::MakeBins(vector<double> &posData)
{
	long binSize = posData.size() + 1;
	vector<double> bin(binSize);
	
	bin[0] = 0.0;
	for (long i = 0; i < posData.size(); ++i) {
		if (posData[i] < 0.0)
			ThrowException("RandomNumberGenerator::MakeBins : negative input");
		
		bin[i+1] = bin[i] + posData[i];
	}
	
	for (long i = 0; i < bin.size() - 1; ++i) 
		bin[i] /= bin[binSize - 1];
	
	bin[binSize - 1] = 1.0;
	
	posData = bin;
	
	return;
}



long RandomNumberGenerator::RandomBin(const vector<double> &bin)
{
	// the output of this function is a randomly selected
	// interval of the input vector bin
	// the intervals are numbered starting at 0 and ending
	// at n-2 where n is the size of bin
	// (hence interval 0 is the space between bin[0] and bin[1], etc.)
	
	// bin must be sorted and have first element = 0 and last element = 1
	
	// check bin limits
	if ((bin[0] != 0.0) || (bin[bin.size()-1] != 1.0))
		ThrowException("RandomNumberGenerator::RandomBin : bad bin end points");
	
	double p = Random01();
	
	// make sure we can handle the endpoints
	if (p == 0.0)
		return 1;
	if (p == 1.0)
		return bin.size() - 2;
		
	return (upper_bound(bin.begin(), bin.end(), p) - bin.begin()) - 1;
}



void RandomNumberGenerator::SpeedTest()
{
	cout << "not implemented" << endl;
	
	return;
}



/* BEGIN RAN2.C 
// this is the numerical recipes file RAN2.C, slightly modified
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-MACHINE_PRECISION_DOUBLE)
//#define RNMX (1.0-EPS)


double RandomNumberGenerator::Ran2(long *idum)
{
	int j;
	long k;
	static long idum2=123456789;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	if (*idum <= 0) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		idum2=(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ1;
			*idum=IA1*(*idum-k*IQ1)-k*IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ1;
	*idum=IA1*(*idum-k*IQ1)-k*IR1;
	if (*idum < 0) *idum += IM1;
	k=idum2/IQ2;
	idum2=IA2*(idum2-k*IQ2)-k*IR2;
	if (idum2 < 0) idum2 += IM2;
	j=iy/NDIV;
	iy=iv[j]-idum2;
	iv[j] = *idum;
	if (iy < 1) iy += IMM1;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}


#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

 END RAN2.C */

