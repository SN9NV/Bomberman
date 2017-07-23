#include "Window.hpp"
#include "Exceptions.hpp"

Window::Window() :
	_window(nullptr),
	_screenWidth(0),
	_screenHeight(0)
{

}

Window::~Window()
{
	SDL_DestroyWindow(this->_window);
}

void Window::create(const std::string &windowName, unsigned screenWidth, unsigned screenHeight, unsigned windowFlags)
{
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;

	Uint32	flags = SDL_WINDOW_OPENGL;

	flags |= (windowFlags & Window::Flags::INVISABLE) ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN;

	if (windowFlags & Window::Flags::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (windowFlags & Window::Flags::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Create SDL window
	this->_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									 this->_screenWidth, this->_screenHeight, flags);

	if (this->_window == nullptr) {
		throw SDL_FatalError("Could not create SDL2 window");
	}

	SDL_GLContext	glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr) {
		throw SDL_FatalError("SDL_GL context could not be created");
	}

	if (glewInit() != GLEW_OK) {
		throw SDL_FatalError("GLEW did not initialize");
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	// Enable VSYNC. Comment to disable
	SDL_GL_SetSwapInterval((windowFlags & Window::Flags::VSYNC_ENABLED) ? 1 : 0);

	if (SDL_GL_GetSwapInterval()) {
		std::cout << "VSYNC is enabled\n";
	} else {
		std::cout << "VSYNC is disabled\n";
	}
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(this->_window);
}

unsigned Window::screenWidth() const
{
	return _screenWidth;
}

unsigned Window::screenHeight() const
{
	return _screenHeight;
}
