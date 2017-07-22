#include "GLSLProgram.hpp"

static std::string	readFileToString(const std::string &filename);
static bool			compileShader(std::string &shaderSRC, GLuint shaderID);

GLSLProgram::GLSLProgram() :
	_vertexShaderID(0),
	_fragmentShaderID(0),
	_programID(0),
	_numAttributes(0) { }

GLSLProgram::~GLSLProgram() {

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
	std::string	VertexShaderSRC = readFileToString(vertexFilePath);
	std::string FragmentShaderSRC = readFileToString(fragmentFilePath);

	if (compileShader(VertexShaderSRC, this->_vertexShaderID)) {
		return true;
	}

	if (compileShader(FragmentShaderSRC, this->_fragmentShaderID)) {
		return true;
	}

	return false;
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

		char	*shaderErrorMessage = new char[InfoLogLength];
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

void GLSLProgram::addAttribute(const std::string &attributeName) {
	glBindAttribLocation(this->_programID, this->_numAttributes++, attributeName.c_str());
}

void GLSLProgram::enable(void) {
	for (unsigned i = 0; i < this->_numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}

	glUseProgram(this->_programID);
}

void GLSLProgram::disable(void) {
	glUseProgram(0);

	for (unsigned i = 0; i < this->_numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
	GLuint location = glGetUniformLocation(this->_programID, uniformName.c_str());

	if (location == GL_INVALID_INDEX) {
		std::cerr << "Uniform variable: " << uniformName << " not found in shader\n";
		exit(1);
	}

	return location;
}

std::string	readFileToString(const std::string &filename) {
	std::ifstream	fileStream(filename, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not open file: " << filename << '\n';
		exit(1);
	}

	return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

bool			compileShader(std::string &shaderSRC, GLuint shaderID) {
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

		char	*shaderErrorMessage = new char[InfoLogLength];
		glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';

		delete[] shaderErrorMessage;

		return true;
	}

	return false;
}
