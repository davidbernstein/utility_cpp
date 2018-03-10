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

#include <iostream>
#include <math.h>

#include "complexmatrix.h"


using namespace std;
using namespace utility;

ComplexMatrix& ComplexMatrix::operator*=(ComplexNumber a)
{
	for (long i = 0; i < mRows; ++i) {
		for (long j = 0; j < mColumns; ++j) {
			mpData[i][j] *= a;
		}
	}
	
	return *this;
}



ComplexMatrix& ComplexMatrix::operator+=(const ComplexMatrix &m)
{
	if (mRows != m.mRows)
		ThrowException("ComplexMatrix::operator+= : unequal number of rows");
	
	if (mColumns != m.mColumns)
		ThrowException("ComplexMatrix::operator+= : unequal number of columns");
    
	for (long i = 0; i < mRows; ++i) {
		for (long j = 0; j < mColumns; ++j) {
			mpData[i][j] += m.mpData[i][j];
		}
	}	
	
	return *this;
}


ComplexMatrix ComplexMatrix::operator*(const ComplexMatrix &m) const
{
    if (mColumns != m.mRows)
        ThrowException("ComplexMatrix::operator* : matrices are wrong size");
    
    ComplexMatrix p(mRows, m.mColumns);
    
    for (short i = 0; i < p.mRows; ++i) {
        for (short j = 0; j < p.mColumns; ++j) {
            p(i, j).Set(0.0, 0.0);
            for (short k = 0; k < mColumns; ++k)
                p(i, j) += (*this)(i, k) * m(k, j);
        }
        
    }
    
    return p;
}



ComplexMatrix ComplexMatrix::Transpose() const
{
    ComplexMatrix result(mColumns, mRows);
    for (short i = 0; i < mRows; ++i) {
        for (short j = 0; j < mColumns; ++j) {
            result(j, i) = mpData[i][j];
        }
        
    }
    
    return result;
}



ComplexMatrix ComplexMatrix::Conjugate() const
{
    ComplexMatrix result(mRows, mColumns);
    for (short i = 0; i < mRows; ++i) {
        for (short j = 0; j < mColumns; ++j) {
            result(i, j) = mpData[i][j].Conjugate();
        }
        
    }
    
    return result;
}



ComplexMatrix ComplexMatrix::Adjoint() const
{
    ComplexMatrix result(mRows, mColumns);
    result = this->Transpose();
    result = result.Conjugate();
    return result;
}



ComplexNumber ComplexMatrix::InnerProduct(const ComplexMatrix &m) const
{
    ComplexMatrix tmp;
    tmp = (this->Adjoint()) * m;
    return tmp.Trace();
}



ComplexMatrix ComplexMatrix::TensorProduct(const ComplexMatrix &a) const
{
    ComplexMatrix b(this->NumRows() * a.NumRows(), this->NumColumns() * a.NumColumns());
 
    long n = a.NumRows();
    long nPrime = a.NumColumns();
    
    for (long j = 0; j < b.NumRows(); ++j) {
        for (long k = 0; k < b.NumColumns(); ++k) {
            long x1 = j / n;
            long x2 = k / nPrime;
            long x3 = j % n;
            long x4 = k % nPrime;
            
            b(j, k) = (*this)(x1, x2) * a(x3, x4);
        }
    }
    
    return b;
}



ComplexNumber ComplexMatrix::Trace(void) const
{
    if (mRows != mColumns) {
        ThrowException("Trace::matrix not square");
    }
    
    ComplexNumber trace;
    for (long i = 0; i < mRows; ++i) {
        trace += mpData[i][i];
    }
    
    return trace;
}



double ComplexMatrix::Norm(void) const
{
    ComplexNumber tmp = this->InnerProduct(*this);
    return sqrt(tmp.RealPart());
}



double ComplexMatrix::Distance(const ComplexMatrix &m) const
{
    // this and m have to be the same dimensions
    if (mRows != m.mRows or mColumns != m.mColumns) {
        ThrowException("ComplexMatrix::Distance: matrices are different dimensions");
    }
    
    ComplexMatrix tmp = *this - m;
    return tmp.Norm();
}



void ComplexMatrix::Print(void) const
{
    for (long i = 0; i < mRows; ++i) {
        this->PrintRow(i);
    }
    
	return;
}


void ComplexMatrix::PrintRow(long i) const
{
    for (long j = 0; j < mColumns; ++j) {
        mpData[i][j].Print();
        cout << "  ";
    }
    cout << "\n";
    
    return;
}

