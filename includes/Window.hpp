#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <iostream>

#include <SDL.h>
#include <GL/glew.h>

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
		~Window();

		void	create(const std::string &windowName, unsigned screenWidth, unsigned screenHeight, unsigned windowFlags);
		void	swapBuffers(void);

		unsigned	screenWidth() const;
		unsigned	screenHeight() const;

	private:
		SDL_Window	*_window;
		unsigned	_screenWidth;
		unsigned	_screenHeight;
};

#endif // WINDOW_HPP
