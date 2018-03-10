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

#ifndef _matrix_h_
#define _matrix_h_

#include "utility.h"
#include "utility.h"

namespace utility {
	template<class T>
	class Matrix {
	public:
		// Constructor
		Matrix(long numRows = 0, long numColumns = 0);

		// Destructor
		virtual ~Matrix(void);
        void Erase(void);

		// copy constructor
		Matrix(const Matrix<T> &m);

		// operators
		Matrix<T>& operator=(const Matrix<T> &m);
		Matrix<T>& operator+=(const Matrix<T> &m);
		T& operator()(long i, long j);
		const T& operator()(long i, long j) const;

		// Sets and Gets
		void SetSize(long numRows, long numColumns);
		long NumRows(void) const;
		long NumColumns(void) const;
        
    protected:
		void ThrowOutOfRangeException(void) const; 

	protected:
		// size
		long mRows;
		long mColumns;

		// data pointer
		T **mpData;
	};
    


	template<class T>
	inline T& Matrix<T>::operator()(long i, long j)
	{
		if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
			ThrowOutOfRangeException();
			
		return mpData[i][j];
	}
	


	template<class T>
	inline const T& Matrix<T>::operator()(long i, long j) const
	{
		if ((i >= mRows) || (i < 0) || (j >= mColumns) || (j < 0))
			ThrowOutOfRangeException();
			
		return mpData[i][j];
	}
	


	template<class T>
	inline Matrix<T>::Matrix(long numRows, long numColumns)
	{
		mpData = NULL;
		mRows = 0;
		mColumns = 0;
		
		SetSize(numRows, numColumns);
	
		return;
	}
	


	template<class T>
	inline Matrix<T>::~Matrix()
	{
		Erase();
		return;
	}



	template<class T>
	inline void Matrix<T>::Erase()
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
	template<class T>
	inline Matrix<T>::Matrix(const Matrix<T> &m)
	{
		*this = m;
		return;
	}



	template<class T>
	inline Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m)
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
	
	
	
	template<class T>
	inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &m)
	{
		if ((m.mRows != mRows) || (m.mColumns != mColumns))
			ThrowException("");
		
		for (long i = 0; i < mRows; ++i) {
            for (long j = 0; j < mColumns; ++j) {
                mpData[i][j] += m.mpData[i][j];
            }
        }
        
		return *this;
	}
	


	template<class T>
	inline void Matrix<T>::SetSize(long numRows, long numColumns)
	{
		if ((mRows == numRows) && (mColumns == numColumns))
			return;

		Erase();

		if ((numRows < 0) || (numColumns < 0))
			ThrowException("Matrix : negative size");
			
		// if either numRows or numColumns is zero then the matrix is left empty
		if ((numRows == 0) || (numColumns == 0))
			return;

		mRows = numRows;
		mColumns = numColumns;
		
		mpData = new T*[mRows];
		for (long i = 0; i < mRows; ++i)
			mpData[i] = new T[mColumns];

		return;
	}



	template<class T>
	inline long Matrix<T>::NumRows() const
	{
		return mRows;
	}
	
	
	
	template<class T>
	inline long Matrix<T>::NumColumns() const
	{
		return mColumns;
	}
	


	template<class T>
	inline void Matrix<T>::ThrowOutOfRangeException() const
	{
		ThrowException("Matrix index out of range");
		return;
	}
}

#endif // _matrix_h_	
