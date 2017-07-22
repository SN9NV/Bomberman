#ifndef GLSLPROGRAM_HPP
#define GLSLPROGRAM_HPP

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class GLSLProgram
{
	public:
		GLSLProgram();
		~GLSLProgram();

		bool	compileShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath);
		bool	linkProgram(void);
		void	addAttribute(const std::string &attributeName);
		void	enable(void);
		void	disable(void);
		GLint	getUniformLocation(const std::string &uniformName);

	private:
		GLuint		_vertexShaderID;
		GLuint		_fragmentShaderID;
		GLuint		_programID;
		unsigned	_numAttributes;
};

#endif // GLSLPROGRAM_HPP
