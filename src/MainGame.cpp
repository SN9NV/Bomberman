#include "MainGame.hpp"

MainGame::MainGame(const std::string &windowName, const unsigned width, const unsigned height) :
	_window(),
	_gameState(MainGame::GameState::RUNNING),
	_time(0.0f),
	_inputManager(this)
{

	this->_camera.init(width, height);

	// Initialize window
	this->_window.create(windowName, width, height, Window::Flags::VSYNC_ENABLED);

	// Create sprites
	this->_sprites.push_back(new Sprite(0.0f, 0.0f, width / 2, width / 2, "images/bomb_party_v4.png"));
	this->_sprites.push_back(new Sprite(width / 2,  0.0f, width / 2, width / 2, "images/bomb_party_v4.png"));

	// Init shaders
	this->_colourProgram.compileShaders("shaders/vertexshader.vsh", "shaders/fragmentshader.fsh");
	this->_colourProgram.addAttribute("vertexPosition");
	this->_colourProgram.addAttribute("vertexColour");
	this->_colourProgram.addAttribute("vertexUV");
	this->_colourProgram.linkProgram();

	this->_inputManager.registerInput(SDLK_w, [](MainGame *mainGame) {
		mainGame->_camera.setPosition(mainGame->_camera.getPosition() + glm::vec2(0.0f, MainGame::CAMERA_SPEED));
	});

	this->_inputManager.registerInput(SDLK_s, [](MainGame *mainGame) {
		mainGame->_camera.setPosition(mainGame->_camera.getPosition() + glm::vec2(0.0f, -MainGame::CAMERA_SPEED));
	});

	this->_inputManager.registerInput(SDLK_a, [](MainGame *mainGame) {
		mainGame->_camera.setPosition(mainGame->_camera.getPosition() + glm::vec2(-MainGame::CAMERA_SPEED, 0.0f));
	});

	this->_inputManager.registerInput(SDLK_d, [](MainGame *mainGame) {
		mainGame->_camera.setPosition(mainGame->_camera.getPosition() + glm::vec2(MainGame::CAMERA_SPEED, 0.0f));
	});

	this->_inputManager.registerInput(SDLK_q, [](MainGame *mainGame) {
		mainGame->_camera.setScale(mainGame->_camera.getScale() + MainGame::SCALE_SPEED);
	});

	this->_inputManager.registerInput(SDLK_e, [](MainGame *mainGame) {
		mainGame->_camera.setScale(mainGame->_camera.getScale() - MainGame::SCALE_SPEED);
	});

	this->_inputManager.registerInput(SDLK_ESCAPE, [](MainGame *mainGame) {
		mainGame->_gameState = MainGame::GameState::WANTS_QUIT;
	});
}

MainGame::~MainGame(void) {
	for (auto &sprite : this->_sprites) {
		delete sprite;
	}

	this->_window.~Window();

	SDL_Quit();
}

void	MainGame::startGameLoop(void) {
	while (this->_gameState != MainGame::GameState::WANTS_QUIT) {
		this->_processInput();
		this->_time += 0.01f;
		this->_camera.update();
		this->_drawGame();
		this->_FPSCounter.fps(true);
	}
}

void	MainGame::_processInput(void) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				this->_gameState = MainGame::GameState::WANTS_QUIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << event.motion.x << " " << event.motion.y << "\n";
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					this->_inputManager.pressKey(event.key.keysym.sym);
				}

				break;
			case SDL_KEYUP:
				this->_inputManager.releaseKey(event.key.keysym.sym);
				break;
		}
	}

	this->_inputManager.processInput();
}

void	MainGame::_drawGame(void) {
	// Clear the screen
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw sprite
	this->_colourProgram.enable();

	glActiveTexture(GL_TEXTURE0);

	GLint	textureLocation = this->_colourProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint	timeLocation = this->_colourProgram.getUniformLocation("time");
	glUniform1f(timeLocation, this->_time);

	GLint	PLocation = this->_colourProgram.getUniformLocation("P");
	glm::mat4	cameraMatrix = this->_camera.getCameraMatrix();
	glUniformMatrix4fv(PLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	for (auto &sprite : this->_sprites) {
		sprite->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	this->_colourProgram.disable();

	// Swap the buffers
	this->_window.swapBuffers();
}
