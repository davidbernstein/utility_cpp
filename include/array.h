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

#ifndef _array_h_
#define _array_h_

#include "utility.h"
#include <string>

#include <list>
#include <set>
#include <vector>

namespace utility {
	void ThrowException(const std::string &message);
}

namespace utility {
	template<class T>
	class Array {
	public:
		// Constructor
		Array(long size = 0);

		// Destructor
		virtual ~Array(void);

		// copy constructor
		Array(const Array<T> &a);

		// operators
		Array<T>& operator=(const Array<T> &a);
		T& operator[](long index);
		const T& operator[](long index) const;
		Array<T>& operator+=(const Array<T> &a);
		Array<T>& operator=(const std::list<T> &l);
		Array<T>& operator=(const std::set<T> &s);
		Array<T>& operator=(const std::vector<T> &v);
		
		// Sets and Gets
		long Size(void) const;
		bool Empty(void) const;
		T* Begin(void);
		const T* Begin(void) const;
		
		// other functions
		void Erase(void);
		void SetSize(long size);

	protected:
		void ThrowOutOfRangeException(void) const;

		// member data
	protected:
		// number of objects in array
		long mSize;

		// pointer to beginning of array
		T *mpData;
	};



	template<class T>
	inline long Array<T>::Size() const
	{
		return mSize;
	}



	template<class T>
	inline bool Array<T>::Empty() const
	{
		return mpData == NULL;
	}
	


	template<class T>
	inline T& Array<T>::operator[](long index)
	{
		if ((index >= mSize) || (index < 0))
			ThrowOutOfRangeException();
			
		return mpData[index];
	}
	


	template<class T>
	inline const T& Array<T>::operator[](long index) const
	{
		if ((index >= mSize) || (index < 0))
			ThrowOutOfRangeException();
			
		return mpData[index];
	}
	


	template<class T>
	inline T* Array<T>::Begin()
	{
		return mpData;
	}
	
	
	template<class T>
	inline const T* Array<T>::Begin() const
	{
		return mpData;
	}

	template<class T>
	inline Array<T>::Array(long size)
	{
		mpData = NULL;
		mSize = 0;
		SetSize(size);
	
		return;
	}
	


	template<class T>
	inline Array<T>::~Array()
	{
		Erase();
		return;
	}



	template<class T>
	inline void Array<T>::Erase()
	{
		if (mpData != NULL) {
			delete [] mpData;
			mpData = NULL;
			mSize = 0;
		} 

		return;
	}



	// copy constructor
	template<class T>
	inline Array<T>::Array(const Array<T> &a)
	{
		mpData = NULL;
		mSize = 0;
		SetSize(a.mSize);

		if (mSize > 0) {
			mpData = new T[mSize];
			for (long i = 0; i < mSize; ++i)
				mpData[i] = a.mpData[i];
		}


		return;
	}



	template<class T>
	inline Array<T>& Array<T>::operator=(const Array<T> &a)
	{
		// check for assignment to self
		if (this == &a)
			return *this;

		SetSize(a.mSize);
		
		for (long i = 0; i < mSize; ++i)
			mpData[i] = a.mpData[i];

		return *this;
	}
	


	template<class T>
	inline Array<T>& Array<T>::operator+=(const Array<T> &a)
	{
		Array<T> tmp(mSize + a.mSize);

		long i;
		for (i = 0; i < mSize; ++i)
			tmp.mpData[i] = mpData[i];

		for (long j = 0; j < a.mSize; ++j)
			tmp.mpData[i + j] = a.mpData[j];

		*this = tmp;

		return *this;
	}



	template<class T>
	inline void Array<T>::SetSize(long size)
	{
		if (mSize == size)
			return;

		Erase();

		if (size == 0)
			return;

		mSize = size;
		mpData = new T[size];


		return;
	}


	
	template<class T>
	inline Array<T>& Array<T>::operator=(const std::list<T> &l)
	{
		SetSize(l.size());
		long i = 0;
		typename std::list<T>::const_iterator iL;
		for (iL = l.begin(); iL != l.end(); ++iL) {
			mpData[i] = *iL;
			++i;
		}
		
		return *this;
	}
	
	
	
	template<class T>
	inline Array<T>& Array<T>::operator=(const std::set<T> &s)
	{
		SetSize(s.size());
		long i = 0;
		typename std::set<T>::const_iterator iS;
		for (iS = s.begin(); iS != s.end(); ++iS) {
			mpData[i] = *iS;
			++i;
		}
		
		return *this;
	}
	
	
	
	template<class T>
	inline Array<T>& Array<T>::operator=(const std::vector<T> &v)
	{
		SetSize(v.size());
		
		for (unsigned long i = 0; i < v.size(); ++i) 
			mpData[i] = v[i];
		
		return *this;
	}
	
	
	
	template<class T>
	inline void Array<T>::ThrowOutOfRangeException() const
	{
		ThrowException("Array index out of range");
		return;
	}
}

#endif // _array_h_	
