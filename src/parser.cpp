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

#include "parser.h"
#include "utility.h"
#include <fstream>
#include <iostream>

using namespace utility;
using namespace std;

Parser::Parser(const string &fileName)
{
	ReadFile(fileName);
	return;
}



void Parser::ReadFile(const string &fileName, bool convertToLowerCase)
{
	// clear existing string
	mWholeFile.clear();
	
	ifstream file;
    OpenInputFile(fileName, file);
			
  	// get length of file
  	file.seekg(0, ios::end);
  	long fileLength = file.tellg();
  	file.seekg(0, ios::beg);

  	// allocate memory and read file as block
  	char *pBuffer = new char[fileLength];
  	file.read(pBuffer, fileLength);
  	
  	// set mWholeFile
	mWholeFile = pBuffer;
	
	// clean up
	delete [] pBuffer;
	file.close();
	
	// remove spaces and comments and convert mWholeFile to lower case
	RemoveCommentLines();
	RemoveSpaces();
	
	if (convertToLowerCase)
		LowerCase(mWholeFile);
	
		
	return;
}



void Parser::RestoreCapitalization(const std::string &token, long numOccurences, const std::string &fileName) 
{
	Parser pTmp;
	pTmp.ReadFile(fileName, false);
	
	bool includeN = numOccurences > 0;
	numOccurences = (numOccurences < 1) ? 1 : numOccurences;
	
	string n;
	for (short i = 1; i <= numOccurences; ++i) {
		n = ConvertIntegerToString(i);
		
		string prefix;
		if (includeN)
			prefix = token + n + "=";
		else
			prefix = token + "=";
			
		string::size_type start;
		if (FindSubString(prefix, start) == false)
			ThrowException("Parser::RestoreCapitalization : bad file data");
		
		string name;
		char tmp = pTmp.mWholeFile[start];
		while (tmp != ';') {
			mWholeFile[start] = tmp;
			++start;
			tmp = pTmp.mWholeFile[start];
		}
	}
	
	
	return;
}



bool Parser::FindInteger(const string &token, long &i) const
{
	string::size_type start;
	if (FindSubString(token, start) == false)
		return false;
	
	char tmp = mWholeFile[start];
	string number;
	while (isdigit(tmp)) {
		number += tmp;
		++start;
		tmp = mWholeFile[start];
	}
	
	i = ConvertStringToInteger(number);
	return true;
}



bool Parser::FindFloat(const string &token, double &value) const
{
	string::size_type start;
	if (FindSubString(token, start) == false)
		return false;
		
	if (ExtractFloat(start, value) != start)
		return true;
	else
		return false;
	
}



bool Parser::FindBracedFloats(const string &token, Array<double> &value) const
{
	string::size_type start;
	if (FindSubString(token, start) == false)
		return false;
	
	list<double> floatList;
	bool found = false;
	while (!found) {
		double x;
		start = ExtractFloat(start, x);
		floatList.push_back(x);
		
		// check for comma
		found = mWholeFile[start] != ',';
		
		// skip over comma
		++start;
	}
	
	value = floatList;
	
	return true;
}



bool Parser::FindString(const std::string &token, std::string &s) const
{
	string::size_type start;
	if (FindSubString(token, start) == false)
		return false;
	
	s.clear();
	char tmp = mWholeFile[start];
	while (isalnum(tmp) || (tmp == '-') || (tmp == '_')) {
		s += tmp;
		++start;
		tmp = mWholeFile[start];
	}
	
	return true;
}



bool Parser::FindFileName(const string &token, string &s) const
{
	string::size_type start;
	if (FindSubString(token, start) == false)
		return false;
	
	s.clear();
	char tmp = mWholeFile[start];
	while (isalnum(tmp) || (tmp == '.') || (tmp == '/') || (tmp == '_')) {
		s += tmp;
		++start;
		tmp = mWholeFile[start];
	}
	
	return true;
}



bool Parser::FindSubString(const string &token, string::size_type &start) const
{
	string::size_type idx = mWholeFile.find(token);
	
	if (idx == string::npos) 
		return false;
	
	start = ((long) idx) + token.length();
	return true;
}



string::size_type Parser::ExtractFloat(const string::size_type &begin, double &value) const
{
	char tmp = mWholeFile[begin];
	if (IsPartOfFloat(tmp) == false)
		return begin;
		
	string number;
	string::size_type current = begin;
	while (IsPartOfFloat(tmp)) {
		number += tmp;
		++current;
		tmp = mWholeFile[current];
	}
	
	value = ConvertStringToFloat(number);
	
	return current;
}

	
	
bool Parser::IsPartOfFloat(const char &c) const
{
	return (isdigit(c) || (c == '+') || (c == '-') || (c == 'e') || (c == 'E') || (c == '.'));
}



void Parser::RemoveSpaces()
{
	unsigned long i = 0;
	while (i < mWholeFile.length()) {
		if (isspace(mWholeFile[i])) 
			mWholeFile.erase(i, 1);
		else
			++i;
	}
	
	return;
}



void Parser::RemoveCommentLines()
{
	unsigned long i = 0;
	bool eraseOn = false;
	while (i < mWholeFile.length()) {
		if (mWholeFile[i] == mCommentCharacter)
			eraseOn = true;
		
		if (eraseOn)
			mWholeFile.erase(i, 1);
		else
			++i;
		
		if (eraseOn && (mWholeFile[i] < 32))
			eraseOn = false;
	}
	
	return;
}
