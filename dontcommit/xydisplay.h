/* * Copyright (C) 2004-2018 David Bernstein <david.h.bernstein@gmail.com> * * This file is part of utility_cpp. * * utility_cpp is free software: you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation, either version 3 of the License, or * (at your option) any later version. * * utility_cpp is distributed in the hope that it will be useful, * but WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the * GNU General Public License for more details. * * You should have received a copy of the GNU General Public License * along with utility_cpp.  If not, see <http://www.gnu.org/licenses/>.*/#ifndef _xydisplay_h_#define _xydisplay_h_#include "xydata.h"#include "vtkXYPlotActor.h"#include "vtkFieldData.h"#include "vtkProperty.h"#include "vtkRenderWindow.h"#include "vtkActor.h"#include "vtkRenderer.h"#include <string>namespace utility {	class XYDisplay {    public:		// Constructors		XYDisplay(void);        		// Destructor        ~XYDisplay(void);                // plotting and showing        void Clear(void);        void Erase(void);        void Show(const XYData &data);                // axes control        void SetXAxisRange(double xMin, double xMax);        void SetYAxisRange(double yMin, double yMax);                // titles        void SetTitle(std::string title);        void SetXTitle(std::string xTitle);        void SetYTitle(std::string yTitle);                // IO        void SaveAsJPEG(const std::string fileName) const;    	void SaveAsPostscript(const std::string fileName) const;    	    private:        void Load(const XYData &data);                    private:    	// vtk data structures        vtkXYPlotActor *mpVtkXYPlotActor;          vtkRenderWindow *mpVtkRenderWindow;        vtkRenderer *mpVtkRenderer;	};}#endif // _xydisplay_h_