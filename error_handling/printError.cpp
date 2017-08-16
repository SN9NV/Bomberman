#include <al.h>
#include "printError.hpp"

static void	printError(int error, const std::string &message) {
	std::cerr << "Error: " << error << ": " << message << std::endl;
}

void	getGLError() {
	GLenum error = glGetError();

	switch (error) {
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			printError(error, "Invalid enum");
			break;
		case GL_INVALID_VALUE:
			printError(error, "Invalid value");
			break;
		case GL_INVALID_OPERATION:
			printError(error, "Invalid operation");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printError(error, "Invalid frame buffer operation");
			break;
		case GL_OUT_OF_MEMORY:
			printError(error, "Out of memory");
			break;
		case GL_STACK_OVERFLOW:
			printError(error, "Stack overflow");
			break;
		case GL_STACK_UNDERFLOW:
			printError(error, "Stack underflow");
			break;
		default:
			printError(error, "Unknown OpenGL error code");
	}
}

void	getALError() {
	ALenum error = alGetError();

	switch (error) {
		case AL_NO_ERROR:
			break;
		case AL_INVALID_NAME:
			printError(error, "Invalid Name parameter passed to AL call");
			break;
		case AL_INVALID_ENUM:
			printError(error, "Invalid enum parameter passed to AL call");
			break;
		case AL_INVALID_VALUE:
			printError(error, "Invalid value parameter passed to AL call");
			break;
		case AL_INVALID_OPERATION:
			printError(error, "Illegal AL call");
			break;
		case AL_OUT_OF_MEMORY:
			printError(error, "No mojo (Not enough memory)");
			break;
		default:
			printError(error, "Unknown OpenAL error code");
	}
}