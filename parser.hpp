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

/** @file parser.hpp
 *  @brief A small GLSL include parser.
 * 
 * 	This is a small class for parsing a shader written in GLSL
 * 	and adding all included files to source similar to what
 * 	a C compiler would do when you #include
 * 
 * 	@namespace SE::Util
 * 	@brief utilities namespace 
 * 	The namespace that holds all utilities in the S-Engine library
 */


#ifndef GLSLPARSER_PARSER_HPP_
#define GLSLPARSER_PARSER_HPP_

#include <string>
#include <regex>

namespace SE::Util
{
	/** @brief Parser is a quick and fast GLSL include parser class.
	 * 
	 *  A class made specifically for GLSL language to make including other shader code easier
	 *  similar to what a `#include <header>` in C would do.
	 *  
	 *  <h1>Example:</h1>
	 *  
	 *  **material.frag**
	 *  @code{.glsl}
	 *  struct Material
	 *  {
	 *  	vec3 Color;
	 *  	sampler2D diffuse;
	 *  };
	 *  
	 *  uniform Material material;
	 *  @endcode
	 *  
	 *  **fragment.frag**
	 *  @code{.glsl}
	 *  #version 330 core
	 *  
	 *  out vec4 FragColor;
	 *  in vec2 TextCoords;
	 *  
	 *  #include <material.frag>
	 *  
	 *  void main()
	 *  {
	 *  	FragColor = vec4(material.Color, 1.0) * texture(material.diffuse, TextCoords);
	 *  }
	 *  @endcode
	 *  
	 */
	class Parser
	{
		/** @privatesection */
	  private:
		/** @brief reads a given file and parses it recursively.
		 * 	
		 * 	The function opens file at filePath and reads it line by line, if any #include tags
		 * 	are found, the function extracts the name of the file and opens it separately for scanning. 
		 * 	@param filePath The actual file to read and parse
		 * 	@param parentDir The directory containing the shader file
		 * 	@returns The content of the file along the content of the included files
		 */
		std::string readFile(const char* filePath, const char* parentDir);
	  public:
		/**
		 * Constructor
		 * @param filePath path for the shader file to parse
		 */
		Parser(const char* filePath);
		/**
		 * The content of the shader file after being parsed
		 */
		std::string content;

	};
}

#endif //GLSLPARSER_PARSER_HPP_
