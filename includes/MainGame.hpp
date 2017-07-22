#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLSLProgram.hpp"
#include "Sprite.hpp"
#include "GLTexture.hpp"
#include "ImageLoader.hpp"

class MainGame {
	public:
		enum GameState {
			RUNNING,
			WANTS_QUIT
		};

		MainGame(const std::string &windowName, const unsigned width, const unsigned height);
		~MainGame(void);

		void startGameLoop(void);

	private:
		std::string	_name;
		unsigned	_width;
		unsigned	_height;
		SDL_Window	*_window;
		GameState	_gameState;
		float		_time;

		std::vector<Sprite *> _sprites;
		GLSLProgram	_colourProgram;

		void		_processInput(void);
		void		_drawGame(void);
};
