#include <LoadGameScreen.hpp>
#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"
#include "sounds/Sounds.hpp"
#include "gui/MainMenuScreen.hpp"
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

	cge::MainMenuScreen	mainMenuScreen(window, &gameState, &sounds);
	cge::LoadGameScreen	loadGameScreen(window, &gameState, &sounds);

	cge::Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	cge::Model cubeModel = cge::Model("resources/moddels/companion.glb", "resources/moddels/companion.png", loader);
	cge::Model bomberModel = cge::Model("resources/moddels/Bomber.glb", "resources/moddels/BomberManTextureDiffuseColor.png", loader);

	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
	cge::Entity	mainMenuBomberman({0.3, 0, 0.5}, {0, 0, 0}, 0.85, bomberModel);
	cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

	while (gameState != cge::GameState::WANTS_QUIT) {

		switch (gameState) {
			case (cge::GameState::PLAY_GAME_PLAY): {
				sounds.PlayMusic(cge::Sounds::Music::LevelOne);

				if (processInput(inputManager)) {
					gameState = cge::GameState::WANTS_QUIT;
				}

				if (inputManager.isKeyPressed(SDLK_c)) {
					std::cout << "Camera:\n" << camera << "\n";
				}

				bomber1.addRotation({0.0f, 0.025f, 0.0f});
				mainMenuBomberman.addRotation({0.05f, 0.0f, 0.0f});
				cube.addRotation({0.0f, 0.0f, 0.05f});

				shader.start();
				renderer.prepare();
				camera.update(shader);

				renderer.render(bomber1);
				renderer.render(mainMenuBomberman);
				renderer.render(cube);
				shader.end();
				window.swapBuffers();
				break;
			}
			case (cge::GameState::PLAY_LOAD_GAME):
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				loadGameScreen.DrawScreen();
				break;
			default:
			case (cge::GameState::PLAY_MAINMENU):
				sounds.PlayMusic(cge::Sounds::Music::Menu);
				mainMenuBomberman.addRotation({0.0f, 0.025f, 0.0f});
				mainMenuScreen.DrawScreen(mainMenuBomberman);
				break;
		}
	}

	return 0;
}

bool processInput(cge::InputManager &inputManager) {
	SDL_Event	event = {};

	while (SDL_PollEvent(&event) > 0) {
		switch (event.type) {
			case SDL_QUIT:
				return true;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					inputManager.pressKey(event.key.keysym.sym);
				}

				break;
			case SDL_KEYUP:
				inputManager.releaseKey(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}

	return inputManager.isKeyPressed(SDLK_ESCAPE);
}