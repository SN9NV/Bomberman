#include "MainGame.hpp"

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
		throw std::runtime_error("Could not create SDL2 window");
	}
}

MainGame::~MainGame(void) {
	SDL_DestroyWindow(this->_window);

	SDL_Quit();
}

void	MainGame::startGameLoop(void) {
	while (this->_gameState != MainGame::GameState::WANTS_QUIT) {
		this->_processInput();
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
