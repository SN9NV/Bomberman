#include <LoadGameScreen.hpp>
#include <GameHUD.hpp>
#include <SaveGameScreen.hpp>
#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"
#include "sounds/Sounds.hpp"
#include "gui/MainMenuScreen.hpp"
#include "gui/OptionsScreen.hpp"
#include "shared.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

bool	processInput(cge::InputManager &inputManager);

int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GLSLProgram	shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	cge::InputManager	inputManager;
	cge::Renderer		renderer(shader);
	cge::Loader			loader;
	cge::Sounds			sounds;

	int gameState = cge::GameState::PLAY_MAINMENU;
	int prevGameState = gameState;

	cge::MainMenuScreen	mainMenuScreen(window, &gameState, &prevGameState, &sounds);
	cge::SaveGameScreen	saveGameScreen(window, &gameState, &sounds);
	cge::LoadGameScreen	loadGameScreen(window, &gameState, &prevGameState, &sounds);
	cge::OptionsScreen	optionsScreen(window, &gameState, &prevGameState, &sounds);
	cge::GameHUD		gameHUD(window, &gameState, &prevGameState, &sounds, &inputManager);

	cge::Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	cge::Model cubeModel = cge::Model("resources/moddels/companion.glb", "resources/moddels/companion.png", loader);
	cge::Model bomberModel = cge::Model("resources/moddels/Bomber.glb", "resources/moddels/BomberManTextureDiffuseColor.png", loader);

	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
	cge::Entity	mainMenuBomberman({0.3, 0, 0.5}, {0, 0, 0}, 0.85, bomberModel);
	cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

	while (gameState != cge::GameState::WANTS_QUIT) {

		switch (gameState) {
			case (cge::GameState::PLAY_GAME_PAUSED):
			case (cge::GameState::PLAY_GAME_PLAY): {
				sounds.PlayMusic(cge::Sounds::Music::LevelOne);

				if (processInput(inputManager)) {
					gameState = cge::GameState::WANTS_QUIT;
				}

				if (inputManager.isKeyPressed(SDLK_c)) {
					std::cout << "Camera:\n" << camera << "\n";
				}

				if (inputManager.isKeyPressed(SDLK_p)) {
					gameState = (gameState == cge::GameState::PLAY_GAME_PLAY) ?
								cge::GameState ::PLAY_GAME_PAUSED : cge::GameState::PLAY_GAME_PLAY;
				}

				if (gameState == cge::GameState::PLAY_GAME_PLAY) {
					bomber1.addRotation({0.0f, 0.025f, 0.0f});
					cube.addRotation({0.0f, 0.0f, 0.05f});
				}

				shader.start();
				renderer.prepare();
				camera.update(shader);
				renderer.render(bomber1);
				renderer.render(mainMenuBomberman);
				renderer.render(cube);
				shader.end();

				//Game HUD, need a condition if the game is paused.
				glDisable(GL_DEPTH_TEST);
				gameHUD.DrawScreen();

				window.swapBuffers();
				break;
			}
			case (cge::GameState::PLAY_SAVE_GAME):
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				saveGameScreen.DrawScreen();
				break;
			case (cge::GameState::PLAY_OPTIONS):
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				optionsScreen.DrawScreen();
				break;
			case (cge::GameState::PLAY_LOAD_GAME):
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				loadGameScreen.DrawScreen();
				break;
			case (cge::GameState::PLAY_MAINMENU):
			default:
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				mainMenuBomberman.addRotation({0.0f, 0.025f, 0.0f});
				mainMenuScreen.DrawScreen(mainMenuBomberman);
				break;
		}
	}

	return 0;
}

bool processInput(cge::InputManager &inputManager) {
	while (SDL_PollEvent(&inputManager.event) > 0) {
		switch (inputManager.event.type) {
			case SDL_QUIT:
				return true;
			case SDL_KEYDOWN:
				if (inputManager.event.key.repeat == 0) {
					inputManager.pressKey(inputManager.event.key.keysym.sym);
				}

				break;
			case SDL_KEYUP:
				inputManager.releaseKey(inputManager.event.key.keysym.sym);
				break;
			default:
				break;
		}
	}

	return inputManager.isKeyPressed(SDLK_ESCAPE);
}