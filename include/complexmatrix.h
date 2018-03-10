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

#ifndef Programming_Drills_ComplexMatrix_h
#define Programming_Drills_ComplexMatrix_h

#include "utility.h"
#include "complexnumber.h"

namespace utility {
	class ComplexMatrix {
    public:
		// Constructor
		ComplexMatrix(long numRows = 0, long numColumns = 0);
        
		// Destructor
		virtual ~ComplexMatrix(void);
        void Erase(void);
        
		// copy constructor
		ComplexMatrix(const ComplexMatrix &m);
        
		// operators
		ComplexMatrix& operator=(const ComplexMatrix &m);
		ComplexNumber& operator()(long i, long j);
		const ComplexNumber& operator()(long i, long j) const;
        ComplexMatrix operator*(const ComplexMatrix &m) const;
		ComplexMatrix& operator*=(ComplexNumber a);
        const ComplexMatrix operator+(const ComplexMatrix &a) const;
        const ComplexMatrix operator-(const ComplexMatrix &a) const;
        ComplexMatrix& operator+=(const ComplexMatrix &m);
		
        // Matrix functions
        ComplexMatrix Transpose(void) const;
        ComplexMatrix Conjugate(void) const;
        ComplexMatrix Adjoint(void) const;
        ComplexNumber InnerProduct(const ComplexMatrix &m) const;
        ComplexNumber Trace(void) const;
        double Norm(void) const;
        double Distance(const ComplexMatrix &m) const;
        ComplexMatrix TensorProduct(const ComplexMatrix &m) const;
        
		// Sets and Gets
		void SetSize(long numRows, long numColumns);
		long NumRows(void) const;
		long NumColumns(void) const;
		
		// various matrix operations
        double Determinant(void) const;
        void MakeRandom(long seed = 1);
		void MakeZero(void);
        void Print(void) const;
        void PrintRow(long i) const;
                
    protected:
		void ThrowOutOfRangeException(void) const; 
        
    protected:
        // size
        long mRows;
		long mColumns;
        
		// data pointer
		ComplexNumber **mpData;
	};
    
    
    
    inline ComplexNumber& ComplexMatrix::operator()(long i, long j)
	{
        if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
            ThrowOutOfRangeException();
        
        return mpData[i][j];
	}
	
    
    
    inline const ComplexNumber& ComplexMatrix::operator()(long i, long j) const
	{
		if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
			ThrowOutOfRangeException();
        
		return mpData[i][j];
	}
	
    
    
    inline ComplexMatrix::ComplexMatrix(long numRows, long numColumns)
	{
        mpData = NULL;
        mRows = 0;
        mColumns = 0;
        
        SetSize(numRows, numColumns);
        
        return;
	}
	
    
    
    inline ComplexMatrix::~ComplexMatrix()
	{
        Erase();
        return;
	}
    
    
    
    inline void ComplexMatrix::Erase()
	{
        if (mpData != NULL) {
            for (long i = 0; i < mRows; ++i)
                delete [] mpData[i];
            
            delete [] mpData;
            
            mpData = NULL;
            mRows = 0;
            mColumns = 0;
        }
        else {
            if ((mRows > 0) || (mColumns > 0))
                ThrowException("Array::Erase : inconsistent data");
        }
        
        
        return;
	}
    
    
    
	// copy constructor
    inline ComplexMatrix::ComplexMatrix(const ComplexMatrix &m)
	{
        *this = m;
        return;
	}
    
    
    
    inline ComplexMatrix& ComplexMatrix::operator=(const ComplexMatrix &m)
	{
        // check for assignment to self
        if (this == &m)
            return *this;
        
        SetSize(m.mRows, m.mColumns);
        
        for (long i = 0; i < mRows; ++i) {
            for (long j = 0; j < mColumns; ++j) {
                mpData[i][j] = m.mpData[i][j];
            }
        }
        
        return *this;
	}
	
	
    
    inline void ComplexMatrix::SetSize(long numRows, long numColumns)
	{
        if ((mRows == numRows) && (mColumns == numColumns))
            return;
        
        Erase();
        
        if ((numRows < 0) || (numColumns < 0))
            ThrowException("Matrix : negative size");
        
        // if either numRows or numColumns is zero then the Matrix is left empty
        if ((numRows == 0) || (numColumns == 0))
            return;
        
        mRows = numRows;
        mColumns = numColumns;
        
        mpData = new ComplexNumber*[mRows];
        for (long i = 0; i < mRows; ++i)
            mpData[i] = new ComplexNumber[mColumns];
        
        return;
	}
    
    
    
    inline long ComplexMatrix::NumRows() const
	{
		return mRows;
	}
	
	
	
    inline long ComplexMatrix::NumColumns() const
	{
		return mColumns;
	}
	
    
    
    inline const ComplexMatrix ComplexMatrix::operator+(const ComplexMatrix &a) const
    {
        ComplexMatrix result(mRows, mColumns);
        
        for (long i = 0; i < mRows; ++i) {
            for (long j = 0; j < mColumns; ++j) {
                result(i, j) = mpData[i][j] + a(i, j);
            }
        }
        
        return result;
    }
    
    
    
    inline const ComplexMatrix ComplexMatrix::operator-(const ComplexMatrix &a) const
    {
        ComplexMatrix result(mRows, mColumns);
        
        for (long i = 0; i < mRows; ++i) {
            for (long j = 0; j < mColumns; ++j) {
                result(i, j) = mpData[i][j] - a(i, j);
            }
        }

        
        return result;
    }
    
    
    
    inline void ComplexMatrix::ThrowOutOfRangeException() const
	{
		ThrowException("Matrix index out of range");
		return;
	}
}

#endif

