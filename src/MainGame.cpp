#include "MainGame.hpp"

MainGame::MainGame(const std::string &windowName, const unsigned width, const unsigned height) :
	_window(),
	_gameState(MainGame::GameState::RUNNING),
	_time(0.0f),
	_screenWidth(width),
	_screenHeight(height),
	_inputManager(this)
{

	this->_camera.init(width, height);

	// Initialize window
	this->_window.create(windowName, width, height, Window::Flags::VSYNC_ENABLED);

	this->_spriteBatch.init();

	// Init shaders
	this->_colourProgram.compileShaders("shaders/vertexshader.vsh", "shaders/fragmentshader.fsh");
	this->_colourProgram.addAttribute("vertexPosition");
	this->_colourProgram.addAttribute("vertexColour");
	this->_colourProgram.addAttribute("vertexUV");
	this->_colourProgram.linkProgram();

	std::cout << "Controlls:\n"
				 "\tW, A, S, D  Move camera\n"
				 "\tQ, E        Zoom in and out\n"
				 "\tV           Toggles VSYNC\n"
				 "\tEscape      Exits the game\n\n";

	// Register the input keys and the functions to run if the key is pressed
	this->_initControls();
}

MainGame::~MainGame(void) {
	this->_window.~Window();

	SDL_Quit();
}

void	MainGame::startGameLoop(void) {
	while (this->_gameState != MainGame::GameState::WANTS_QUIT) {
		this->_processInput();
		this->_time += 0.01f;
		this->_camera.update();

		auto projectile = this->_projectiles.begin();
		while(projectile != this->_projectiles.end()) {
			if ((*projectile)->update()) {
				projectile = this->_projectiles.erase(projectile);
			} else {
				projectile++;
			}
		}

		this->_drawGame();
		this->_FPSCounter.fps(true);
	}
}

void MainGame::_initControls()
{
	this->_inputManager.registerInput(SDLK_w, [](MainGame *mainGame) {
		mainGame->_camera.addPosition(glm::vec2(0.0f, MainGame::CAMERA_SPEED));
	});

	this->_inputManager.registerInput(SDLK_s, [](MainGame *mainGame) {
		mainGame->_camera.addPosition(glm::vec2(0.0f, -MainGame::CAMERA_SPEED));
	});

	this->_inputManager.registerInput(SDLK_a, [](MainGame *mainGame) {
		mainGame->_camera.addPosition(glm::vec2(-MainGame::CAMERA_SPEED, 0.0f));
	});

	this->_inputManager.registerInput(SDLK_d, [](MainGame *mainGame) {
		mainGame->_camera.addPosition(glm::vec2(MainGame::CAMERA_SPEED, 0.0f));
	});

	this->_inputManager.registerInput(SDLK_q, [](MainGame *mainGame) {
		mainGame->_camera.addScale(MainGame::SCALE_SPEED);
	});

	this->_inputManager.registerInput(SDLK_e, [](MainGame *mainGame) {
		mainGame->_camera.addScale(-MainGame::SCALE_SPEED);
	});

	this->_inputManager.registerInput(SDLK_ESCAPE, [](MainGame *mainGame) {
		mainGame->_gameState = MainGame::GameState::WANTS_QUIT;
	});

	this->_inputManager.registerInput(SDLK_v, [](MainGame *mainGame) {
		(void)mainGame;
		SDL_GL_SetSwapInterval(SDL_GL_GetSwapInterval() ? 0 : 1);
	});

	// Mouse button functions
	this->_inputManager.registerInput(SDL_BUTTON_LEFT, [](MainGame *mainGame) {
		glm::vec2	mouseCoords = mainGame->_camera.screenToWorldCoords(mainGame->_inputManager.getMouseCoords());
		std::cout << "Mouse position: " << mouseCoords.x << ", " << mouseCoords.y << "\n";

		glm::vec2	playerPosition(0.0f, 0.0f);
		glm::vec2	direction = glm::normalize(mouseCoords - playerPosition);

		mainGame->_projectiles.push_back(new Projectile(playerPosition, direction, 1.0f, 1000));
	});
}

void	MainGame::_processInput(void) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				this->_gameState = MainGame::GameState::WANTS_QUIT;
				break;
			case SDL_MOUSEMOTION:
				this->_inputManager.setMouseCoords(event.motion.x, event.motion.y);
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					this->_inputManager.pressKey(event.key.keysym.sym);
				}

				break;
			case SDL_KEYUP:
				this->_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				this->_inputManager.releaseKey(event.button.button);
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

	// Set up camera matrix
	GLint	PLocation = this->_colourProgram.getUniformLocation("P");
	glm::mat4	cameraMatrix = this->_camera.getCameraMatrix();
	glUniformMatrix4fv(PLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	this->_spriteBatch.begin();

	glm::vec4	position(0.0f, 0.0f, this->_screenWidth / 2.0f, this->_screenHeight / 2.0f);
	GLTexture	texture = ResourceManager::getTexture("images/bomb_party_v4.png");

	this->_spriteBatch.draw(position, texture.id, 0.0f, { 255, 255, 255, 255 });

	for(auto &projectile : this->_projectiles) {
		projectile->draw(this->_spriteBatch);
	}

	this->_spriteBatch.end();
	this->_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	this->_colourProgram.disable();

	// Swap the buffers
	this->_window.swapBuffers();
}
