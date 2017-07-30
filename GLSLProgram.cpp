#include <iostream>
#include "GLSLProgram.hpp"

GLSLProgram::GLSLProgram() :
	_vertexShaderID(0),
	_fragmentShaderID(0),
	_programID(0),
	_attributeCount(0)
{
	this->compileShaders("../vertex.glsl", "../fragment.glsl");

//	uniform mat4 transformationMatrix;
//	uniform mat4 projectionMatrix;
//	uniform mat4 viewMatrix;

	this->bindAttribute("transformationMatrix");
	this->bindAttribute("projectionMatrix");
	this->bindAttribute("viewMatrix");

	this->linkProgram();
}

bool GLSLProgram::compileShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
	// Create program and shader ID's
	this->_programID = glCreateProgram();
	this->_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	this->_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (this->_vertexShaderID == 0 || this->_fragmentShaderID == 0) {
		std::cerr << "Could not create vertex or fragment shader ID's\n";
		return true;
	}

	// Read shaders from file
	std::string	VertexShaderSRC = IO::readFileToString(vertexFilePath);
	std::string FragmentShaderSRC = IO::readFileToString(fragmentFilePath);

	if (this->_compileShader(VertexShaderSRC, this->_vertexShaderID)) {
		return true;
	}

	return this->_compileShader(FragmentShaderSRC, this->_fragmentShaderID);

}

bool GLSLProgram::linkProgram() {
	// Link the program
	glAttachShader(this->_programID, this->_vertexShaderID);
	glAttachShader(this->_programID, this->_fragmentShaderID);
	glLinkProgram(this->_programID);

	GLint	success = GL_FALSE;

	glGetProgramiv(this->_programID, GL_LINK_STATUS, &success);

	if (success == GL_FALSE) {
		int		InfoLogLength;
		glGetProgramiv(this->_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		auto	*shaderErrorMessage = new char[InfoLogLength];
		glGetShaderInfoLog(this->_programID, InfoLogLength, nullptr, shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';

		delete[] shaderErrorMessage;

		return true;
	}

	glDetachShader(this->_programID, this->_vertexShaderID);
	glDetachShader(this->_programID, this->_fragmentShaderID);

	glDeleteShader(this->_vertexShaderID);
	glDeleteShader(this->_fragmentShaderID);

	this->_vertexShaderID = 0;
	this->_fragmentShaderID = 0;

	return false;
}

void GLSLProgram::bindAttribute(const std::string &attributeName) {
	glBindAttribLocation(this->_programID, this->_attributeCount++, attributeName.c_str());
}

void GLSLProgram::start() {
	for (unsigned i = 0; i < this->_attributeCount; i++) {
		glEnableVertexAttribArray(i);
	}

	glUseProgram(this->_programID);
}

void GLSLProgram::end() {
	glUseProgram(0);

	for (unsigned i = 0; i < this->_attributeCount; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
	GLint location = glGetUniformLocation(this->_programID, uniformName.c_str());

	if (static_cast<GLuint>(location) == GL_INVALID_INDEX) {
		std::cerr << "Uniform variable: " << uniformName << " not found in shader\n";
		exit(1);
	}

	return location;
}

void GLSLProgram::uploadFloat(GLint location, float value) {
	glUniform1f(location, value);
}

void GLSLProgram::uploadvec3d(GLint location, const glm::vec3 &value) {
	glUniform3f(location, value.x, value.y, value.z);
}

void GLSLProgram::uploadBool(GLint location, bool value) {
	glUniform1ui(location, value ? 1 : 0);
}

void GLSLProgram::uploadMatrix4f(GLint location, const glm::mat4 &value) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

bool GLSLProgram::_compileShader(const std::string &shaderSRC, GLuint shaderID) {
	// Convert shader to char array
	const char *shaderSRCPointer = shaderSRC.c_str();

	// Compile shader
	glShaderSource(shaderID, 1, &shaderSRCPointer, nullptr);
	glCompileShader(shaderID);

	GLint	success = GL_FALSE;

	// Check for errors in the Shader's source code
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		int		InfoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		auto	*shaderErrorMessage = new char[InfoLogLength];
		glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';

		delete[] shaderErrorMessage;

		return true;
	}

	return false;
}
