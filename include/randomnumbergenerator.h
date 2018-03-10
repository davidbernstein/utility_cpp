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

#ifndef _randomnumbergenerator_h_
#define _randomnumbergenerator_h_

#include "utilityenums.h"
#include "utility.h"
#include "array.h"
#include "constants.h"

#include <vector>

namespace utility {
	class RandomNumberGenerator {
    public:
		RandomNumberGenerator();
		
        // set seed
        void Reset(void);
        void Reset(long seed);
        void Reset(long seed, RandomNumberGeneratorType type);
        
        // seed
        long Seed(void) const;
        
        // random numbers
        double Random01(void);
        double RandomNumber(double lowerLimit = 0.0, double upperLimit = 1.0);
        long RandomInteger(long lowerLimit, long upperLimit);
        long FloorOrCeiling(double posNumber);
        
        // binning
        void MakeBins(std::vector<double> &posData);
        long RandomBin(const std::vector<double> &bin);
        
        // calls
        long NumCalls(void) const;
        
        // numerical recipes     
		double Ran2(long *idum);
		double Ran3(long *idum);
		
		double Lsfr258(void);

        // testing
        void SpeedTest(void);
        
    private:
        // seed (must be negative)
        long mSeed;
        
        // number of calls with fixed seed
        long mNumCalls;
        
        // type of generator
        RandomNumberGeneratorType mGeneratorType;
        
        // dummy integer for numerial recipes calls
        long mIdum;
        
        // 5% of the period of ran1 is about 100 million
        // (ran2 has a period of about 2 X 10^18, so we don't worry about that)
        static const long RAN1_PERIOD_WARNING = 100000000;
	};


    
    inline long RandomNumberGenerator::Seed() const
    {
        return mSeed;
    }
    
    
    
    inline long RandomNumberGenerator::NumCalls() const
    {
    	return mNumCalls;
    }
    
    


	inline double RandomNumberGenerator::Random01()
	{
		++mNumCalls;
	
		switch (mGeneratorType) {
        	case RAN2:
           		return Ran2(&mIdum);
            	break;
            	
            case RAN3:
           		return Ran3(&mIdum);
            	break;
            
			case LSFR258:
				return Lsfr258();
				break;
            
        	default:
            	ThrowException("Random01 : RANDOM_NUMBER_GENERATOR not set");
            	return -1.0;
            	break;
		}
	}

    
    /* BEGIN RAN2.C */
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


inline double RandomNumberGenerator::Ran2(long *idum)
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

/* END RAN2.C */


/* BEGIN RAN3.C */
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

inline double RandomNumberGenerator::Ran3(long *idum)
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
/* END RAN3.C */


/* BEGIN LSFR258 */
inline double RandomNumberGenerator::Lsfr258()
{
	static unsigned long long z1, z2, z3, z4, z5;
	
	ThrowException("RandomNumberGenerator::Lsfr258 : uncomment z3");
	
	if (mIdum < 0) {
		z1 = -mIdum;
	
		z2 = 9879879;
		//z3 = 98985876587587;
		z4 = 133;
		z5 = 550;
	}
	else {
		mIdum = 1;
	}
	
	unsigned long long b;
	
	b = (((z1 <<  1) ^ z1) >> 53);
	z1 = (((z1 & 18446744073709551614ULL) << 10) ^ b);
	
	b = (((z2 << 24) ^ z2) >> 50);
	z2 = (((z2 & 18446744073709551104ULL) <<  5) ^ b);
	
	b = (((z3 <<  3) ^ z3) >> 23);
	z3 = (((z3 & 18446744073709547520ULL) << 29) ^ b);
	
	b = (((z4 <<  5) ^ z4) >> 24);
	z4 = (((z4 & 18446744073709420544ULL) << 23) ^ b);
	
	b = (((z5 <<  3) ^ z5) >> 33);
	z5 = (((z5 & 18446744073701163008ULL) <<  8) ^ b);
	
	return ((z1 ^ z2 ^ z3 ^ z4 ^ z5) * 5.4210108624275221e-20);
}
/* END LSFR258 */
}


#endif // _randomnumbergenerator_h_
