//
// Created by spounka on 25/06/2020.
//

/*
 * MIT License
 * Copyright (c) 2020 Spounka Von Schpeiner
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */


#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <regex>

namespace SE::Util
{

	// A function that extracts the file name from a given line
	std::string extractFileName(const std::string& line);

	Parser::Parser(const char* filePath)
	{
		std::string dir = filePath;
		std::string parentDir = dir.substr(0, dir.find_last_of('/')) + '/';
		content = readFile(filePath, parentDir.c_str());
	}
	std::string Parser::readFile(const char* filePath, const char* parentDir)
	{
		std::string output, line;
		int lineNumber = 1;
		std::regex re("^[[:space:]]*#[[:space:]]*include(.)*>$");
		std::ifstream file;
		file.open(filePath);
		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);

				if (std::regex_match(line, re))
				{
					std::string substr = extractFileName(line);
					output.append(readFile((parentDir + substr).c_str(), parentDir));
				}
				else
					output.append(line + "\n");
				lineNumber++;
			}
			file.close();
		}
		else
		{
			std::cerr << "Error while trying to open/read file at " << filePath << std::endl;
			file.close();
		}

		return output;
	}
	std::string extractFileName(const std::string& line)
	{
		std::smatch match;
		std::regex fileInc("<.*>");
		std::regex_search(line, match, fileInc);
		std::string strMatch = match.str();
		unsigned start = strMatch.find('<');
		unsigned end = strMatch.find('>');
		return match.str().substr(++start, --end);
	}

}

