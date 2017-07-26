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
#include "InputManager.hpp"
#include "FPSCounter.hpp"
#include "SpriteBatch.hpp"
#include "Projectile.hpp"

class MainGame {
	public:
		enum GameState {
			RUNNING,
			WANTS_QUIT
		};

		static constexpr float	CAMERA_SPEED = 8.0f;
		static constexpr float	SCALE_SPEED = 0.1f;

		MainGame(const std::string &windowName, const unsigned width, const unsigned height);
		~MainGame(void);

		void startGameLoop(void);

	private:
		Window		_window;
		GameState	_gameState;
		float		_time;
		unsigned	_screenWidth;
		unsigned	_screenHeight;


		std::vector<Sprite *>		_sprites;
		GLSLProgram					_colourProgram;
		Camera2D					_camera;
		InputManager<MainGame>		_inputManager;
		FPSCounter					_FPSCounter;
		SpriteBatch					_spriteBatch;
		std::vector<Projectile *>	_projectiles;

		void		_initControls(void);
		void		_processInput(void);
		void		_drawGame(void);
};
