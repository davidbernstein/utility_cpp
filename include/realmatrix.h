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

#ifndef _realmatrix_h_
#define _realmatrix_h_

#include "utility.h"
#include "matrix.h"

namespace utility {
	template<>
	class Matrix<double> {
    public:
		// Constructor
		Matrix(long numRows = 0, long numColumns = 0);
        
		// Destructor
		virtual ~Matrix(void);
        void Erase(void);
        
		// copy constructor
		Matrix(const Matrix<double> &m);
        
		// operators
		Matrix<double>& operator=(const Matrix<double> &m);
		double& operator()(long i, long j);
		const double& operator()(long i, long j) const;
        Matrix<double> operator*(const Matrix<double> &m) const;
		Matrix<double>& operator*=(double a);
        Matrix<double>& operator+=(const Matrix<double> &m);
		
		// Sets and Gets
		void SetSize(long numRows, long numColumns);
		long NumRows(void) const;
		long NumColumns(void) const;
		
		// various matrix operations
        double Determinant(void) const;
        void MakeRandom(long seed = 1);
		void MakeZero(void);
        void Print(void) const;
        void Inverse(Matrix<double> &inv) const;
        
        // numerical recipes
    	void lubksb(double **a, int n, int *indx, double b[]) const;
    	void ludcmp(double **a, int n, int *indx, double *d) const;
        
    protected:
        void MakeNRMatrix(Matrix<double> &nr) const;
		void ThrowOutOfRangeException(void) const; 
        
    protected:
        // size
        long mRows;
		long mColumns;
        
		// data pointer
		double **mpData;
	};
    
    
    
    inline double& Matrix<double>::operator()(long i, long j)
	{
        if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
            ThrowOutOfRangeException();
			
        return mpData[i][j];
	}
	
    
    
    inline const double& Matrix<double>::operator()(long i, long j) const
	{
		if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
			ThrowOutOfRangeException();
        
		return mpData[i][j];
	}
	
    
    
    inline Matrix<double>::Matrix(long numRows, long numColumns)
	{
        mpData = NULL;
        mRows = 0;
        mColumns = 0;
            
        SetSize(numRows, numColumns);
            
        return;
	}
	
    
    
    inline Matrix<double>::~Matrix()
	{
        Erase();
        return;
	}
    
    
    
    inline void Matrix<double>::Erase()
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
    inline Matrix<double>::Matrix(const Matrix<double> &m)
	{
        *this = m;
        return;
	}
    
    
    
    inline Matrix<double>& Matrix<double>::operator=(const Matrix<double> &m)
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
	
	
    
    inline void Matrix<double>::SetSize(long numRows, long numColumns)
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
            
        mpData = new double*[mRows];
        for (long i = 0; i < mRows; ++i)
            mpData[i] = new double[mColumns];
            
        return;
	}
    
    
    
    inline long Matrix<double>::NumRows() const
	{
		return mRows;
	}
	
	
	
    inline long Matrix<double>::NumColumns() const
	{
		return mColumns;
	}
	
    
    
    inline void Matrix<double>::ThrowOutOfRangeException() const
	{
		ThrowException("Matrix index out of range");
		return;
	}
}

#endif // _realmatrix_h_	


