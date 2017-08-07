#include "Window.hpp"
#include "Loader.hpp"
#include "GLSLProgram.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

bool	processInput(cge::InputManager &inputManager);

int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GLSLProgram	shader("../Testvertex.glsl", "../Textfragment.glsl");
	cge::InputManager	inputManager;
	cge::Renderer		renderer(shader);
	cge::Loader			loader;

	cge::Camera camera(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), window);

	enum GameState {
		PLAY,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY;

	//cge::Model cubeModel = cge::Model("../resources/moddels/companion.glb", "../resources/moddels/companion.png", loader);
	cge::Model bomberModel = cge::Model("../resources/moddels/Bomber.glb", "../resources/moddels/BomberManTextureDiffuseColor.png", loader);
	cge::Model bomberModel2 = cge::Model("../resources/moddels/Bomber.glb", "../resources/moddels/BomberManTextureDiffuseColor.png", loader);

	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
	cge::Entity	bomber2({0.75, 2, -1}, {0, 0, 0}, 0.5, bomberModel);
	//cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState ::WANTS_QUIT;
		}

		if (inputManager.isKeyPressed(SDLK_c)) {
			std::cout << "Camera:\n" << camera << "\n";
		}

		bomber1.addRotation({0.0f, 0.01f, 0.0f});
		bomber2.addRotation({0.01f, 0.0f, 0.0f});
		//cube.addRotation({0.0f, 0.0f, 0.01f});


		shader.start();
			renderer.prepare();

			camera.update(shader);

			renderer.render(bomber1);
			renderer.render(bomber2);
		//	renderer.render(cube);
		shader.end();
		window.swapBuffers();
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