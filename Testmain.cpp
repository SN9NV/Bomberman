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

bool	processInput(InputManager &inputManager);

int main() {
	Window			window("Bomberman", WIDTH, HEIGHT, Window::Flags::VSYNC_ENABLED);
	GLSLProgram		shader("../Testvertex.glsl", "../Textfragment.glsl");
	InputManager	inputManager;
	Renderer		renderer(shader);
	Loader			loader;

	tinygltf::Model model1;
	tinygltf::Model model2;
	tinygltf::TinyGLTF glTFLoader;
	std::string err;

	glTFLoader.LoadBinaryFromFile(&model1, &err, "../resources/moddels/bomner2.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../resources/moddels/cube.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../resources/moddels/unwrappedCube.glb");
//	glTFLoader.LoadBinaryFromFile(&model2, &err, "../resources/moddels/doubleCube.glb");
	glTFLoader.LoadBinaryFromFile(&model2, &err, "../resources/moddels/companion.glb");

	Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	enum GameState {
		PLAY,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY;

	shader.start();
	Model fullModelBomber = Model(model1, loader.loadTexture("../resources/moddels/BomBerTextureDiffuseColor.png"));
	Model fullModelCube = Model(model2, loader.loadTexture("../resources/moddels/companion.png"));
	shader.end();

	Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, fullModelBomber);
	Entity	bomber2({0.75, 2, -1}, {0, 0, 0}, 0.5, fullModelBomber);
	Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, fullModelCube);

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState ::WANTS_QUIT;
		}

		if (inputManager.isKeyPressed(SDLK_c)) {
			std::cout << "Camera:\n" << camera << "\n";
		}

		bomber1.addRotation({0.0f, 0.01f, 0.0f});
		bomber2.addRotation({0.01f, 0.0f, 0.0f});
		cube.addRotation({0.0f, 0.0f, 0.01f});


		shader.start();

		renderer.prepare();

		camera.update(inputManager, shader);

		renderer.render(bomber1);
		renderer.render(bomber2);
		renderer.render(cube);

		shader.end();
		window.swapBuffers();
	}

	return 0;
}

bool processInput(InputManager &inputManager) {
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

