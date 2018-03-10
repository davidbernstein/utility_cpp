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

#include "realmatrix.h"
#include "randomnumbergenerator.h"

#include <iostream>

using namespace utility;
using namespace std;

Matrix<double>& Matrix<double>::operator*=(double a)
{
	for (long i = 0; i < mRows; ++i) {
		for (long j = 0; j < mColumns; ++j) {
			mpData[i][j] *= a;
		}
	}
	
	return *this;
}



Matrix<double>& Matrix<double>::operator+=(const Matrix<double> &m)
{
	if (mRows != m.mRows)
		ThrowException("Matrix<double>::operator+= : unequal number of rows");
	
	if (mColumns != m.mColumns)
		ThrowException("Matrix<double>::operator+= : unequal number of columns");
		
	for (long i = 0; i < mRows; ++i) {
		for (long j = 0; j < mColumns; ++j) {
			mpData[i][j] += m.mpData[i][j];
		}
	}	
	
	return *this;
}



void Matrix<double>::Inverse(Matrix<double> &inv) const
{
    double d;
    int *indx = new int[mRows + 1];
    
    Matrix<double> tmp;
    MakeNRMatrix(tmp);
    
    ludcmp(tmp.mpData, mRows, indx, &d);
    
    double *col = new double[mRows + 1];
    
    inv.SetSize(mRows, mColumns);
    
    for (short j = 1; j <= mRows; ++j) {
        for (short i = 1; i <= mRows; ++i) 
            col[i] = 0.0;
        
        col[j] = 1.0;
        lubksb(tmp.mpData, mRows, indx, col); 
        for (short i = 1; i <= mRows; ++i) 
            inv(i-1, j-1) = col[i];
    }
    
    delete [] indx;
    delete [] col;
    
    return;
}



double Matrix<double>::Determinant() const
{
    double d = 0.0;
    int *indx = new int[mRows + 1];
    
    Matrix<double> tmp;
    MakeNRMatrix(tmp);
    
    ludcmp(tmp.mpData, mRows, indx, &d);
    
    for (short i = 1; i <= mRows; ++i) {
        // should check for under/over flow
        d *= tmp(i, i);
    }
    
    delete [] indx;
    
    return d;
}



Matrix<double> Matrix<double>::operator*(const Matrix<double> &m) const
{
    if (mColumns != m.mRows)
        ThrowException("Matrix<double>::operator* : matrices are wrong size");
        
    Matrix<double> p(mRows, m.mColumns);

    for (short i = 0; i < p.mRows; ++i) {
        for (short j = 0; j < p.mColumns; ++j) {
            p(i, j) = 0.0;
            for (short k = 0; k < p.mColumns; ++k)
                p(i, j) += (*this)(i, k) * m(k, j);
        }
        
    }
    
    return p;
}



void Matrix<double>::MakeZero()
{
    for (short i = 0; i < mRows; ++i) {
        for (short j = 0; j < mColumns; ++j) {
            mpData[i][j] = 0.0;
        }
    }
    
    return;
}



void Matrix<double>::MakeRandom(long seed)
{
    RandomNumberGenerator rng;
    rng.Reset(seed);
    
    for (short i = 0; i < mRows; ++i) {
        for (short j = 0; j < mColumns; ++j) {
            mpData[i][j] = rng.Random01();
        }
    }
    
    return;
}



void Matrix<double>::MakeNRMatrix(Matrix<double> &nr) const
{
    nr.SetSize(mRows + 1, mColumns + 1);
    
    for (short i = 1; i <= mRows; ++i) {
        for (short j = 1; j <= mColumns; ++j) 
            nr.mpData[i][j] = mpData[i-1][j-1];
    }
    
    for (short i = 0; i < nr.mRows; ++i) 
        nr.mpData[i][0] = 0.0;
    
    for (short i = 0; i < nr.mColumns; ++i) 
        nr.mpData[0][i] = 0.0;
    
    return;
}



void Matrix<double>::Print() const
{
    for (short i = 0; i < mRows; ++i) {
        for (short j = 0; j < mColumns; ++j) {
            cout << mpData[i][j] << " ";
        }
        cout << endl;
    }
    
    return;
}


// begin NR routine ludcmp
#define TINY 1.0e-20;
void Matrix<double>::ludcmp(double **a, int n, int *indx, double *d) const
{
	int i,imax,j,k;
	double big,dum,sum,temp;
    
    Array<double> vv(n+1);
    //vv=vector(1,n);
    
	*d=1.0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if ((temp=fabs(a[i][j])) > big) big=temp;
		if (big == 0.0) ThrowException("Singular matrix in routine ludcmp");
		vv[i]=1.0/big;
	}
	for (j=1;j<=n;j++) {
		for (i=1;i<j;i++) {
			sum=a[i][j];
			for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for (i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if ( (dum=vv[i]*fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		if (j != imax) {
			for (k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			*d = -(*d);
			vv[imax]=vv[j];
		}
		indx[j]=imax;
		if (a[j][j] == 0.0) a[j][j]=TINY;
		if (j != n) {
			dum=1.0/(a[j][j]);
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	//free_vector(vv,1,n);
}
#undef TINY
// End NR routine ludcmp


// begin NR routine lubksb
void Matrix<double>::lubksb(double **a, int n, int *indx, double b[]) const
{
	int i,ii=0,ip,j;
	double sum;

	for (i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if (sum) ii=i;
		b[i]=sum;
	}
	for (i=n;i>=1;i--) {
		sum=b[i];
		for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		b[i]=sum/a[i][i];
	}
}
// end NR routine lubksb
