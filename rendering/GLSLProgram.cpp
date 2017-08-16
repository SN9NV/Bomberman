#include <iostream>
#include "GLSLProgram.hpp"

namespace cge {
	GLSLProgram::GLSLProgram(const std::string &vertexFilePath, const std::string &fragmentFilePath) :
			_vertexShaderID(0),
			_fragmentShaderID(0),
			_programID(0),
			_attributeCount(0),
			_isInUse(false)
	{
		this->compileShaders(vertexFilePath, fragmentFilePath);
		this->linkProgram();
	}

	bool GLSLProgram::compileShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
		/// Create program and shader ID's
		this->_programID = glCreateProgram();
		this->_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		this->_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (this->_vertexShaderID == 0 || this->_fragmentShaderID == 0) {
			std::cerr << "Could not create vertex or fragment shader ID's\n";
			return true;
		}

		/// Read shaders from file
		std::string	VertexShaderSRC = IO::readFileToString(vertexFilePath);
		std::string FragmentShaderSRC = IO::readFileToString(fragmentFilePath);
		std::cout << "compiling " << vertexFilePath << std::endl;
		if (this->_compileShader(VertexShaderSRC, this->_vertexShaderID)) {
			return true;
		}
		std::cout << "compiling " << fragmentFilePath << std::endl;
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
		this->_isInUse = true;
	}

	void GLSLProgram::end() {
		glUseProgram(0);
		this->_isInUse = false;

		for (unsigned i = 0; i < this->_attributeCount; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	GLint GLSLProgram::getUniformLocation(const std::string &uniformName) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		GLint location = glGetUniformLocation(this->_programID, uniformName.c_str());

		if (static_cast<GLuint>(location) == GL_INVALID_INDEX) {
			std::cerr << "Uniform variable: " << uniformName << " not found in shader\n";
			exit(1);
		}

		return location;
	}

	void GLSLProgram::uploadFloat(GLint location, float value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniform1f(location, value);
	}

	void GLSLProgram::uploadvec3d(GLint location, const glm::vec3 &value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniform3f(location, value.x, value.y, value.z);
	}

	void GLSLProgram::uploadBool(GLint location, bool value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniform1ui(location, value ? 1 : 0);
	}

	void GLSLProgram::uploadMatrix4f(GLint location, const glm::mat4 &value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}

	bool GLSLProgram::_compileShader(const std::string &shaderSRC, GLuint shaderID) {
		/// Convert shader to char array
		const char *shaderSRCPointer = shaderSRC.c_str();

		/// Compile shader
		glShaderSource(shaderID, 1, &shaderSRCPointer, nullptr);
		glCompileShader(shaderID);

		GLint	success = GL_FALSE;

		/// Check for errors in the Shader's source code
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

	void GLSLProgram::upload1i(GLint location, GLint value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniform1i(location, value);
	}

	void GLSLProgram::uploadvec2d(GLint location, const glm::vec2 &value) const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}

		glUniform2f(location, value.x, value.y);
	}
}