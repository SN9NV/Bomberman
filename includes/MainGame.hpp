#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Window.hpp"
#include "GLSLProgram.hpp"
#include "Sprite.hpp"
#include "GLTexture.hpp"
#include "ImageLoader.hpp"
#include "Camera2D.hpp"

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
		Window		_window;
		GameState	_gameState;
		float		_time;
		float		_fps;
		float		_frameTime;
		float		_maxFPS;

		std::vector<Sprite *>	_sprites;
		GLSLProgram				_colourProgram;
		Camera2D				_camera;

		void		_processInput(void);
		void		_drawGame(void);
		void		_calculateFPS(void);
};
