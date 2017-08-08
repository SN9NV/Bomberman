#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"
#include "sounds/Sounds.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

bool	processInput(cge::InputManager &inputManager);

int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GLSLProgram	shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	cge::InputManager	inputManager;
	cge::Renderer		renderer(shader);
	cge::Loader			loader;
	cge::Sounds			sounds;

	cge::Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	enum GameState {
		PLAY_GAME,
		PLAY_GAME_PAUSED,
		PLAY_MAINMENU,
		PLAY_OPTIONS,
		PLAY_SAVE_GAME,
		PLAY_LOAD_GAME,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY_GAME;

	cge::Model cubeModel = cge::Model("../resources/moddels/companion.glb", "../resources/moddels/companion.png", loader);
	cge::Model bomberModel = cge::Model("../resources/moddels/Bomber.glb", "../resources/moddels/BomberManTextureDiffuseColor.png", loader);

	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
	cge::Entity	bomber2({0.75, 2, -1}, {0, 0, 0}, 0.5, bomberModel);
	cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState::WANTS_QUIT;
		}

		switch (gameState) {
			case (GameState::PLAY_GAME): {
				sounds.PlayMusic(cge::Sounds::Music::Menu);

				if (inputManager.isKeyPressed(SDLK_c)) {
					std::cout << "Camera:\n" << camera << "\n";
				}

				bomber1.addRotation({0.0f, 0.01f, 0.0f});
				bomber2.addRotation({0.01f, 0.0f, 0.0f});
				cube.addRotation({0.0f, 0.0f, 0.01f});

				shader.start();
				renderer.prepare();
				camera.update(shader);

				renderer.render(bomber1);
				renderer.render(bomber2);
				renderer.render(cube);
				shader.end();
				window.swapBuffers();
				break;
			}
			default:
			case (GameState::PLAY_MAINMENU):
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