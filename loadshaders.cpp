#include "loadshaders.hpp"

static std::string	readFileToString(const char *filename) {
	std::ifstream	fileStream(filename, std::ios::in);

	if (VertexShaderStream.is_open()) {
		return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	} else {
		std::cerr << "Could not open file: " << filename << '\n';
	}
}

static bool			compileShader(std::string &shaderSRC, GLuint shaderID) {
	// Convert shader to char array
	const char *shaderSRCPointer = shaderSRC.c_str();

	// Compile shader
	glShaderSource(shaderID, 1, shaderSRCPointer, nullptr);
	glCompileShader(shaderID);

	int		InfoLogLength;

	// Check for errors in the Shader's source code
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength) {
		char shaderErrorMessage[InfoLogLength];
		glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, &shaderErrorMessage);
		std::cerr << "Shader compilation error:\n" << shaderErrorMessage << '\n';
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


}
