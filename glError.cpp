#include "glError.hpp"

void	getGLError() {
	GLenum error = glGetError();

	switch (error) {
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			std::cout << "Error: " << error << " Invalid enum\n";
			break;
		case GL_INVALID_VALUE:
			std::cout << "Error: " << error << " Invalid value\n";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "Error: " << error << " Invalid operation\n";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "Error: " << error << "Invalid frambuffer operation\n";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "Error: " << error << " Out of memory\n";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "Error: " << error << " Stack underflow\n";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "Error: " << error << " Stack underflow\n";
			break;
		default:
			std::cout << "Error: " << error << "\n";
	}
}