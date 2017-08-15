#include <OpenAL/OpenAL.h>
#include "printError.hpp"

void	getGLError() {
	GLenum error = glGetError();

	switch (error) {
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			std::cout << "Error: " << error << " Invalid enum" << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "Error: " << error << " Invalid value" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "Error: " << error << " Invalid operation" << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "Error: " << error << " Invalid frambuffer operation" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "Error: " << error << " Out of memory" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "Error: " << error << " Stack underflow" << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "Error: " << error << " Stack underflow" << std::endl;
			break;
		default:
			std::cout << "Error: " << error << std::endl;
	}
}

void	getALError() {
	ALenum error = alGetError();

	switch (error) {
		case AL_NO_ERROR:
			break;
		case AL_INVALID_NAME:
			std::cout << "Error: " << error << " Invalid Name parameter passed to AL call." << std::endl;
			break;
		case AL_INVALID_ENUM:
			std::cout << "Error: " << error << " Invalid parameter passed to AL call." << std::endl;
			break;
		case AL_INVALID_VALUE:
			std::cout << "Error: " << error << " Invalid enum parameter value." << std::endl;
			break;
		case AL_INVALID_OPERATION:
			std::cout << "Error: " << error << " Illegal call." << std::endl;
			break;
		case AL_OUT_OF_MEMORY:
			std::cout << "Error: " << error << " No mojo. (Out of memory)" << std::endl;
			break;
		default:
			std::cout << "Error: " << error << std::endl;
	}
}