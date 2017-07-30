#ifndef NEW_WINDOW_HPP
#define NEW_WINDOW_HPP

#include <string>

#include <SDL.h>

#include "Exceptions.hpp"

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
	void	swapBuffers();

	unsigned	getWidth() const;
	unsigned	getHeight() const;

private:
	unsigned	_width;
	unsigned	_height;

	SDL_Window	*_window;
};


#endif //NEW_WINDOW_HPP
