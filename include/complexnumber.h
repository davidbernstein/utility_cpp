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

#ifndef _ComplexNumber_h
#define _ComplexNumber_h

#include <math.h>
#include "utility.h"

#define PI 3.14159265358979

namespace utility {
    class ComplexNumber
    {
    public:
        // Constructors
        ComplexNumber(void);
        ComplexNumber(double real, double imaginary);
        
        // Destructor
        ~ComplexNumber(void) { };
        
        // sets
        void Set(double real, double imaginary);
    
        // gets
        double RealPart(void) const;
        double ImaginaryPart(void) const;
        double Modulus(void) const;
        double ModulusSquared(void) const;

        // overloading
        ComplexNumber& operator=(const ComplexNumber &a);
        const ComplexNumber operator+(const ComplexNumber &a) const;
        const ComplexNumber operator-(const ComplexNumber &a) const;
        const ComplexNumber operator*(const ComplexNumber &a) const;
        const ComplexNumber operator/(const ComplexNumber &a) const;
        ComplexNumber& operator+=(const ComplexNumber &a);
        ComplexNumber& operator*=(const ComplexNumber &a);

        // conjugate
        const ComplexNumber Conjugate(void) const;
    
        // polar coordinates
        double Phase(void) const;

        // debugging
        void Print(void) const;
    
    private:
        // real part
        double mReal;
		
        // imaginary part
        double mImaginary;
    };



    inline ComplexNumber::ComplexNumber(void)
    {
        mReal = 0.0;
        mImaginary = 0.0;
        return;
    }


    inline ComplexNumber::ComplexNumber(double real, double imaginary)
    {
        mReal = real;
        mImaginary = imaginary;
    
        return;
    }



    inline void ComplexNumber::Set(double real, double imaginary)
    {
        mReal = real;
        mImaginary = imaginary;
    
        return;
    }


    inline double ComplexNumber::Modulus(void) const
    {
        return sqrt(mReal * mReal + mImaginary * mImaginary);
    }



    inline double ComplexNumber::ModulusSquared(void) const
    {
        return mReal * mReal + mImaginary * mImaginary;
    }



    inline ComplexNumber& ComplexNumber::operator=(const ComplexNumber &a)
    {
        mReal = a.mReal;
        mImaginary = a.mImaginary;
        return *this;
    }



    inline const ComplexNumber ComplexNumber::operator+(const ComplexNumber &a) const
    {
        ComplexNumber result;
    
        result.mReal = this->mReal + a.mReal;
        result.mImaginary = this->mImaginary + a.mImaginary;
    
        return result;
    }



    inline const ComplexNumber ComplexNumber::operator-(const ComplexNumber &a) const
    {
        ComplexNumber result;
    
        result.mReal = this->mReal - a.mReal;
        result.mImaginary = this->mImaginary - a.mImaginary;
    
        return result;
    }



    inline const ComplexNumber ComplexNumber::operator*(const ComplexNumber &a) const
    {
        ComplexNumber result;
    
        result.mReal = this->mReal * a.mReal - this->mImaginary * a.mImaginary;
        result.mImaginary = this->mReal * a.mImaginary + this->mImaginary * a.mReal;
    
        return result;
    }
    
    
    
    inline ComplexNumber& ComplexNumber::operator+=(const ComplexNumber &a)
    {
        mReal += a.mReal;
        mImaginary += a.mImaginary;
        return *this;
    }
    
    
    
    inline ComplexNumber& ComplexNumber::operator*=(const ComplexNumber &a)
    {
        ComplexNumber tmp = *this;
        *this = tmp * a;
        return *this;
    }



    inline const ComplexNumber ComplexNumber::operator/(const ComplexNumber &a) const
    {
        ComplexNumber result;
    
        double denom = a.ModulusSquared();
        if (denom == 0.0) {
            return result;
        }
    
        result.mReal = (this->mReal * a.mReal + this->mImaginary * a.mImaginary) / denom;
        result.mImaginary = (this->mImaginary * a.mReal - this->mReal * a.mImaginary) / denom;
    
        return result;
    }



    inline double ComplexNumber::RealPart() const
    {
        return mReal;
    }
	


    inline double ComplexNumber::ImaginaryPart() const
    {
        return mImaginary;
    }



    inline const ComplexNumber ComplexNumber::Conjugate(void) const
    {
        ComplexNumber result;
        result.mReal = this->mReal;
        result.mImaginary = -this->mImaginary;
        return result;
    }
}
#endif
