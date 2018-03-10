/* * Copyright (C) 2004-2018 David Bernstein <david.h.bernstein@gmail.com> * * This file is part of utility_cpp. * * utility_cpp is free software: you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation, either version 3 of the License, or * (at your option) any later version. * * utility_cpp is distributed in the hope that it will be useful, * but WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the * GNU General Public License for more details. * * You should have received a copy of the GNU General Public License * along with utility_cpp.  If not, see <http://www.gnu.org/licenses/>.*/#ifndef _xydata_h_#define _xydata_h_#include "utility.h"#include "utility.h"#include "array.h"#include "realmatrix.h"#include "mesh.h"#include <string>namespace utility {	class XYData {	public:		XYData(short numColumns = 1);		~XYData(void) { };		// data		void AddX(double x);		void AddY(double y, short column = 1);		std::vector<double>& GetYValues(short column = 1);		std::vector<double>& GetXValues(void);		const std::vector<double>& GetYValues(short column = 1) const;		const std::vector<double>& GetXValues(void) const;		void EraseData(void);		long NumColumns(void) const;				// for showing 1D meshes		void Make(const Mesh &mesh, short speciesNumber = 0);				// for showing matrix values		void Make(const Matrix<double> &m, short rowIndex);				// title and labels		void SetTitle(std::string title);		void SetXLabel(std::string xLabel);		void SetYLabel(std::string yLabel, short column = 1);			private:					private:		Array<std::vector<double> > mData;				std::string mTitle;		std::string mXLabel;		Array<std::string> mYLabel;				static const short mInitialVectorReserve = 500;	};				inline long XYData::NumColumns() const	{		return mData.Size() - 1;	}				inline void XYData::EraseData()	{		for (short i = 0; i < mData.Size(); ++i)			ResizeVector(mData[i], 0);				return;	}				inline XYData::XYData(short numColumns)	{		mData.SetSize(numColumns + 1);				for (short i = 0; i < mData.Size(); ++i)			mData[i].reserve(mInitialVectorReserve);					return;	}				inline std::vector<double>& XYData::GetYValues(short column)	{		return mData[column];	}				inline std::vector<double>& XYData::GetXValues()	{		return mData[0];	}				inline const std::vector<double>& XYData::GetYValues(short column) const	{		return mData[column];	}				inline const std::vector<double>& XYData::GetXValues() const	{		return mData[0];	}				inline void XYData::AddX(double x)	{		mData[0].push_back(x);		return;	}				inline void XYData::AddY(double y, short column)	{		if (column < 1)			ThrowException("XYData::AddY : bad column index");				mData[column].push_back(y);		return;	}}#endif // _xydata_h_