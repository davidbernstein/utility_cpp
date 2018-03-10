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

#ifndef _parser_h_
#define _parser_h_

#include <string>
#include "array.h"

namespace utility {
	class Parser {
	public:
		Parser(void) { };
		Parser(const std::string &fileName);
		
		~Parser(void) { };
		
		// file reading
		void ReadFile(const std::string &fileName, bool convertToLowerCase = true);
		
		// number extraction
		bool FindInteger(const std::string &token, long &i) const;
		bool FindFloat(const std::string &token, double &value) const;
		bool FindBracedFloats(const std::string &token, Array<double> &value) const;
		bool FindString(const std::string &token, std::string &s) const;
		bool FindFileName(const std::string &token, std::string &s) const;
		
		// capitalization
		void RestoreCapitalization(const std::string &token, long numOccurences, const std::string &fileName);
	
	private:	
		bool FindSubString(const std::string &token, std::string::size_type &start) const;
		void RemoveSpaces(void);
		void RemoveCommentLines(void);
		bool IsPartOfFloat(const char &c) const;
		std::string::size_type ExtractFloat(const std::string::size_type &begin, double &value) const;
		
	private:
		std::string mWholeFile;
		
		const static char mCommentCharacter = '%';
	};
}


#endif // _parser_h_

