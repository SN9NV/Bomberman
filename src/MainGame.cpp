#include "MainGame.hpp"

MainGame::MainGame(const std::string &windowName, const unsigned width, const unsigned height) :
	_window(),
	_gameState(MainGame::GameState::RUNNING),
	_time(0.0f),
	_maxFPS(60.0f)
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
		this->_calculateFPS();
	}
}

void	MainGame::_processInput(void) {
	SDL_Event	event;

	const float	CAMERA_SPEED = 20.0f;
	const float	SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				this->_gameState = MainGame::GameState::WANTS_QUIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << event.motion.x << " " << event.motion.y << "\n";
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_w:
						this->_camera.setPosition(this->_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
						break;
					case SDLK_s:
						this->_camera.setPosition(this->_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
						break;
					case SDLK_a:
						this->_camera.setPosition(this->_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
						break;
					case SDLK_d:
						this->_camera.setPosition(this->_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
						break;
					case SDLK_q:
						this->_camera.setScale(this->_camera.getScale() + SCALE_SPEED);
						break;
					case SDLK_e:
						this->_camera.setScale(this->_camera.getScale() - SCALE_SPEED);
						break;
				}

				break;
		}
	}
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

void MainGame::_calculateFPS(void) {
	static const unsigned	NUM_SAMPLES = 100;
	static float			frameTime[NUM_SAMPLES];
	static unsigned			currentFrame = 0;
	static float			previousTicks = SDL_GetTicks();

	float	currentTicks = SDL_GetTicks();
	this->_frameTime = currentTicks - previousTicks;
	previousTicks = currentTicks;

	frameTime[currentFrame++ % NUM_SAMPLES] = this->_frameTime;

	float averageFrameTime = 0;

	for (unsigned i = 0; i < NUM_SAMPLES; i++) {
		averageFrameTime += frameTime[i];
	}

	averageFrameTime /= NUM_SAMPLES;

	if (averageFrameTime > 0) {
		this->_fps = 1000 / averageFrameTime;
	} else {
		this->_fps = 0;
	}

	if (!(currentFrame % NUM_SAMPLES)) {
		std::cout << this->_fps << "\n";
	}
}
