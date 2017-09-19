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

	void GLSLProgram::begin() {
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
		this->_checkInUse();
		GLint location = glGetUniformLocation(this->_programID, uniformName.c_str());

		if (location == static_cast<GLint>(GL_INVALID_INDEX)) {
			std::cerr << "Uniform variable: " << uniformName << " not found in shader\n";
		}

		return location;
	}

	void GLSLProgram::uploadFloat(GLint location, float value) const {
		this->_checkInUse();
		glUniform1f(location, value);
	}

	void GLSLProgram::uploadvec3d(GLint location, const glm::vec3 &value) const {
		this->_checkInUse();
		glUniform3f(location, value.x, value.y, value.z);
	}

	void GLSLProgram::uploadBool(GLint location, bool value) const {
		this->_checkInUse();
		glUniform1ui(location, value ? 1 : 0);
	}

	void GLSLProgram::uploadBool(const std::string &uniformName, bool value) const {
		this->uploadBool(this->getUniformLocation(uniformName), value);
	}

	void GLSLProgram::uploadMatrix4f(GLint location, const glm::mat4 &value) const {
		this->_checkInUse();
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}

	void GLSLProgram::uploadMatrix4f(const std::string &uniformName, const glm::mat4 &value) const {
		this->uploadMatrix4f(this->getUniformLocation(uniformName), value);
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
		this->_checkInUse();
		glUniform1i(location, value);
	}

	void GLSLProgram::uploadvec2d(GLint location, const glm::vec2 &value) const {
		this->_checkInUse();
		glUniform2f(location, value.x, value.y);
	}

	GLint GLSLProgram::getAttributeLocation(const std::string &attrName) const {
		this->_checkInUse();
		GLint attribute = glGetAttribLocation(this->_programID, attrName.c_str());

		if (attribute == static_cast<GLint>(GL_INVALID_INDEX)) {
			std::cerr << "Could not bind attribute: " << attrName << std::endl;
		}

		return (attribute);
	}

	bool GLSLProgram::isInUse() const {
		return this->_isInUse;
	}

	void GLSLProgram::_checkInUse() const {
		if (!this->_isInUse) {
			std::cerr << "Program is not in use\n";
		}
	}

	void GLSLProgram::uploadMatrix4f(GLint location, const std::vector<glm::mat4> &values) const {
		glUniformMatrix4fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, (GLfloat *)values.data());
	}
}
