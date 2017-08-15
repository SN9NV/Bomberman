#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"
#include "sounds/Sounds.hpp"
#include "extras/tinygltfOstream.hpp"
#include "extras/glmOstream.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tinyGLTF/tiny_gltf.h"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1280;

bool	processInput(cge::InputManager &inputManager);

int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GLSLProgram	shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	cge::InputManager	inputManager;
	cge::Renderer		renderer(shader);
	cge::Loader			loader;
//	cge::Sounds			sounds;

	cge::Camera camera(glm::vec3(0.8f, 1.6f, 1.75f), glm::vec3(0.5f, -0.4f, 0.0f), window);

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

//	cge::Model cubeModel = cge::Model("resources/models/companion.glb", "resources/models/companion.png", loader);
	cge::Model bomberModel = cge::Model("resources/models/Bomber.glb", "resources/models/BomberManTextureDiffuseColor.png", loader);
//	cge::Model bomberModel = cge::Model("resources/models/WingBoot.glb", "resources/models/BomberManTextureDiffuseColor.png", loader);
//	cge::Model bomberModel = cge::Model("resources/models/run.glb", "resources/models/BomberManTextureDiffuseColor.png", loader);
//	cge::Model bomberModel = cge::Model("resources/models/dumb.glb", "resources/models/image.png", loader);

//	std::cout << bomberModel.getTinygltfModel();

	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
//	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 0.5, dumbModel);
//	cge::Entity	bomber2({0.75, 2, -1}, {0, 0, 0}, 0.5, bomberModel);
//	cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

//	bomber1.setAnimationSpeed(2.0);

	bool	showWeights = false;
	bool	isInvisible = false;

	shader.start();
		shader.uploadBool(shader.getUniformLocation("showWeights"), showWeights);
		shader.uploadBool(shader.getUniformLocation("isInvisible"), isInvisible);
	shader.end();

	unsigned debounce = SDL_GetTicks();

	bool	paused = false;

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState::WANTS_QUIT;
		}

		switch (gameState) {
			case (GameState::PLAY_GAME): {
//				sounds.PlayMusic(cge::Sounds::Music::Menu);

				if (inputManager.isKeyPressed(SDLK_c) && debounce + 1000 < SDL_GetTicks()) {
					std::cout << "Camera:\n" << camera << "\n";
					debounce = SDL_GetTicks();
				}

				if (inputManager.isKeyPressed(SDLK_w)) {
					camera.addRotation({0, 0.1, 0});
				}
				if (inputManager.isKeyPressed(SDLK_a)) {
					camera.addRotation({-0.1, 0, 0});
				}
				if (inputManager.isKeyPressed(SDLK_s)) {
					camera.addRotation({0, -0.1, 0});
				}
				if (inputManager.isKeyPressed(SDLK_d)) {
					camera.addRotation({0.1, 0, 0});
				}
				if (inputManager.isKeyPressed(SDLK_r)) {
					bomber1.setAnimationTicks(0.0);
				}
				if (inputManager.isKeyPressed(SDLK_KP_PLUS)) {
					bomber1.setAnimationSpeed(bomber1.getAnimationSpeed() + 1.0f);
				}
				if (inputManager.isKeyPressed(SDLK_KP_MINUS)) {
					bomber1.setAnimationSpeed(bomber1.getAnimationSpeed() - 1.0f);
				}
				if (inputManager.isKeyPressed(SDLK_KP_0)) {
					bomber1.setAnimationSpeed(1.0);
				}

//				bomber1.addRotation({0.0f, 0.025f, 0.0f});
//				bomber2.addRotation({0.05f, 0.0f, 0.0f});
//				cube.addRotation({0.0f, 0.0f, 0.05f});

				shader.start();

				if (inputManager.isKeyPressed(SDLK_x) && debounce + 1000 < SDL_GetTicks()) {
					showWeights = !showWeights;
					shader.uploadBool(shader.getUniformLocation("showWeights"), showWeights);
					debounce = SDL_GetTicks();
				}

				if (inputManager.isKeyPressed(SDLK_z) && debounce + 1000 < SDL_GetTicks()) {
					isInvisible = !isInvisible;
					shader.uploadBool(shader.getUniformLocation("isInvisible"), isInvisible);
					debounce = SDL_GetTicks();
				}

				if (inputManager.isKeyPressed(SDLK_p) && debounce + 1000 < SDL_GetTicks()) {
					paused = !paused;
					debounce = SDL_GetTicks();
				}

				if (!paused) {
					bomber1.update(shader, true);
//					dumb.update(shader, true, 1);
				}

				renderer.prepare();
				camera.update(shader);

				renderer.render(bomber1);
//				renderer.render(dumb);
//				renderer.render(bomber2);
//				renderer.render(cube);
				shader.end();
				window.swapBuffers();

				SDL_Delay(0);
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