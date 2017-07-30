#include <GL/glew.h>
#include <iostream>
#include "Window.hpp"

Window::Window() :
		_width(0),
		_height(0),
		_window(nullptr)
{

}

Window::~Window() {
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

void Window::create(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags) {
	this->_width = width;
	this->_height = height;

	Uint32	flags = SDL_WINDOW_OPENGL;

	flags |= static_cast<bool>((windowFlags & Window::Flags::INVISABLE)) ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN;

	if (static_cast<bool>(windowFlags & Window::Flags::FULLSCREEN)) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (static_cast<bool>(windowFlags & Window::Flags::BORDERLESS)) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	this->_window = SDL_CreateWindow(
			windowName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			this->_width,
			this->_height,
			flags);

	if (this->_window == nullptr) {
		throw SDL_FatalError("Could not create SDL2 window");
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext	glContext = SDL_GL_CreateContext(this->_window);

	if (glContext == nullptr) {
		throw SDL_FatalError("SDL_GL context could not be created");
	}

	if (glewInit() != GLEW_OK) {
		throw SDL_FatalError("GLEW did not initialize");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

	// Enable VSYNC. Comment to disable
	SDL_GL_SetSwapInterval(static_cast<bool>((windowFlags & Window::Flags::VSYNC_ENABLED)) ? 1 : 0);

	if (static_cast<bool>(SDL_GL_GetSwapInterval())) {
		std::cout << "VSYNC is enabled\n";
	} else {
		std::cout << "VSYNC is disabled\n";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::swapBuffers() {
	SDL_GL_SwapWindow(this->_window);
}

Window::Window(const Window &window) {
	*this = window;
}

unsigned Window::getWidth() const {
	return this->_width;
}

unsigned Window::getHeight() const {
	return this->_height;
}

Window::Window(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags) {
	this->create(windowName, width, height, windowFlags);
}
