#include <iostream>

#include "MainGame.hpp"

constexpr unsigned	WIDTH = 1024;
constexpr unsigned	HEIGHT = 768;

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	MainGame	mainGame(std::string("Bomberman"), WIDTH, HEIGHT);

	mainGame.startGameLoop();

	return 0;
}
