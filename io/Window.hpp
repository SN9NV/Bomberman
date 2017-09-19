#ifndef NEW_WINDOW_HPP
#define NEW_WINDOW_HPP

#include <string>
#include <iostream>
#include <glfw/include/GLFW/glfw3.h>
#include "../error_handling/Exceptions.hpp"
#include "settings/Settings.hpp"
#include "../loaders/Loader.hpp"

namespace cge {
	class Window {
	public:
		enum Flags {
			DEFAULT			= 0,
			INVISABLE		= 1,
			FULLSCREEN		= 2,
			BORDERLESS		= 4,
			VSYNC_ENABLED	= 8
		};

		Window();
		virtual ~Window();

		Window(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags);

		Window(const Window &window);

		Window &operator=(const Window &rhs) = default;

		void	create(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags);
		void	recreate(unsigned width, unsigned height);
		void	swapBuffers();

		unsigned	getWidth() const;
		unsigned	getHeight() const;
		unsigned	getFrameTime() const;
		GLFWwindow	*getGLFWWindow() const;

	private:
		unsigned	_width;
		unsigned	_height;
		unsigned	_lastFrameTime;
		unsigned	_deltaFrameTime;

		GLFWwindow*	_glfwWindow;
		cge::Loader	_loader;
	};
}

#endif //NEW_WINDOW_HPP
