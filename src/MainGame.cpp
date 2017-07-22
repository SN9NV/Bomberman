#include "MainGame.hpp"

static void	SDL_FatalError(std::string message) {
	std::cout << message << "\n";
	SDL_Quit();
	exit(1);
}

MainGame::MainGame(const std::string &windowName, const unsigned width, const unsigned height) :
		_name(windowName),
		_width(width),
		_height(height),
		_gameState(MainGame::GameState::RUNNING) {
	SDL_Init(SDL_INIT_EVERYTHING);

	this->_window = SDL_CreateWindow(this->_name.c_str(),
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 this->_width,
									 this->_height,
									 SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (this->_window == nullptr) {
		SDL_FatalError("Could not create SDL2 window");
	}

	SDL_GLContext	glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr) {
		SDL_FatalError("SDL_GL context could not be created");
	}

	if (glewInit() != GLEW_OK) {
		SDL_FatalError("GLEW did not initialize");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	// Init sprite
	this->_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	// Init shaders
	this->_colourProgram.compileShaders("shaders/vertexshader.vsh", "shaders/fragmentshader.fsh");
	this->_colourProgram.addAttribute("vertexPosition");
	this->_colourProgram.addAttribute("vertexColour");
	this->_colourProgram.linkProgram();
}

MainGame::~MainGame(void) {
	SDL_DestroyWindow(this->_window);

	SDL_Quit();
}

void	MainGame::startGameLoop(void) {
	while (this->_gameState != MainGame::GameState::WANTS_QUIT) {
		this->_processInput();
		this->_drawGame();
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
				std::cout << event.motion.x << " " << event.motion.y << "\n";
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
	this->_sprite.draw();
	this->_colourProgram.disable();

	// Swap the buffers
	SDL_GL_SwapWindow(this->_window);
}
