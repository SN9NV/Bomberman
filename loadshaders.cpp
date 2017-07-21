#include "loadshaders.hpp"

static std::string	readFileToString(const char *filename) {
	std::ifstream	fileStream(filename, std::ios::in);

	if (fileStream.is_open()) {
		return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	} else {
		std::cerr << "Could not open file: " << filename << '\n';
	}

	return std::string(nullptr);
}

static bool			compileShader(std::string &shaderSRC, GLuint shaderID) {
	// Convert shader to char array
	const char *shaderSRCPointer = shaderSRC.c_str();

	// Compile shader
	glShaderSource(shaderID, 1, &shaderSRCPointer, nullptr);
	glCompileShader(shaderID);

	int		InfoLogLength;
	GLint	Result = GL_FALSE;

	// Check for errors in the Shader's source code
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength) {
		char *shaderErrorMessage = new char[InfoLogLength];
		glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';

		delete[] shaderErrorMessage;
	}

	return (InfoLogLength);
}

GLuint	LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
	// Create shader ID's
	GLuint	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader from file
	std::string	VertexShaderSRC = readFileToString(vertex_file_path);

	// Read Fragment shader from file
	std::string FragmentShaderSRC = readFileToString(fragment_file_path);

	GLint	result = GL_FALSE;
	int		InfoLogLength;

	compileShader(VertexShaderSRC, VertexShaderID);
	compileShader(FragmentShaderSRC, FragmentShaderID);

	// Create and link the program
	GLuint	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength) {
		char *shaderErrorMessage = new char[InfoLogLength];

		glGetShaderInfoLog(programID, InfoLogLength, nullptr, shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';

		delete[] shaderErrorMessage;
	}

	glDetachShader(programID, VertexShaderID);
	glDetachShader(programID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return programID;
}
