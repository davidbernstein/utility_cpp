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

#ifndef _circulararray_h_
#define _circulararray_h_

#include "array.h"

namespace utility {
	template<class T>
	class CircularArray : public Array<T> {
	public:
		// Constructor
		//CircularArray(long size = 0) : Array(size) { };

		// use destructor and copy constructer inherited from Array
		
		// index operator
		T& operator[](long index);
		const T& operator[](long index) const;
		
	private:
		long Index(long index) const;
	};
	
	
    
	template<class T>
	inline long CircularArray<T>::Index(long index) const
	{
		long i = abs(index) % this->Size();
		
		if (i == 0)
			return 0;
			
		if (index < 0) 
			i = this->Size() - i;
			
		return i;
	}
	


	template<class T>
	inline T& CircularArray<T>::operator[](long index)
	{	
		return (this->Begin())[Index(index)];
	}
	


	template<class T>
	inline const T& CircularArray<T>::operator[](long index) const
	{
		return (this->Begin())[Index(index)];
	}
}

#endif // _circulararray_h_	
