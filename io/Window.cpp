
#include "Window.hpp"

namespace cge {
	Window::Window() :
			_width(0),
			_height(0),
			_lastFrameTime(SDL_GetTicks()),
			_glfwWindow(nullptr)
	{

	}

	Window::~Window() {
		glfwDestroyWindow(this->_glfwWindow);
		glfwTerminate();
	}

	void Window::create(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags) {
		this->_width = width;
		this->_height = height;
		this->_lastFrameTime = glfwGetTime();

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_SAMPLES, 0);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_STENCIL_BITS, 8);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		this->_glfwWindow = glfwCreateWindow(
			this->_width,
			this->_height,
			windowName.c_str(),
			nullptr,
			nullptr
		);
		glfwMakeContextCurrent(this->_glfwWindow);
		glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (this->_glfwWindow == nullptr) {
			throw SDL_FatalError("Could not create SDL2 window");
		}

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			throw SDL_FatalError("GLEW did not initialize");
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

		/// Enable VSYNC?
		glfwSwapInterval(static_cast<bool>((windowFlags & Window::Flags::VSYNC_ENABLED)) ? 1 : 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::swapBuffers() {
		unsigned currentTime = glfwGetTime();
		this->_deltaFrameTime = currentTime - this->_lastFrameTime;
		this->_lastFrameTime = currentTime;

		glfwSwapBuffers(this->_glfwWindow);
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

	unsigned Window::getFrameTime() const {
		return this->_deltaFrameTime;
	}

	GLFWwindow *Window::getGLFWWindow() const {
		return (this->_glfwWindow);
	}
}