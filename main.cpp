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
static constexpr unsigned WIDTH = 1024;

bool	processInput(cge::InputManager &inputManager);

int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
//	cge::GLSLProgram	shader("shaders/vertex.glsl", "shaders/fragment.glsl");
//	cge::InputManager	inputManager;
//	cge::Renderer		renderer(shader);
	cge::Loader			loader;
//	cge::Sounds			sounds;

//	cge::Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	enum GameState {
		PLAY_GAME,
		PLAY_GAME_PAUSED,
		PLAY_MAINMENU,
		PLAY_OPTIONS,
		PLAY_SAVE_GAME,
		PLAY_LOAD_GAME,
		WANTS_QUIT
	};

//	int gameState = GameState::PLAY_GAME;

//	cge::Model cubeModel = cge::Model("resources/moddels/companion.glb", "resources/moddels/companion.png", loader);
	cge::Model bomberModel = cge::Model("resources/moddels/Bomber2.glb", "resources/moddels/BomberManTextureDiffuseColor.png", loader);

	tinygltf::Model model = bomberModel.getTinygltfModel();
	tinygltf::Buffer buffer = model.buffers[0];

	std::cout << "::::MODEL::::\n" << model << "\n\n";

	std::cout << "::::NODES::::\n";
	for (auto &node : model.nodes) {
		std::cout << node << "\n\n";
	}

	std::cout << "::::SKINS::::\n";
	for (auto &skin : model.skins) {
		std::cout << skin << "\n\n";
	}

	std::cout << "::::ANIMATIONS::::\n";
	for (auto &animation : model.animations) {
		std::cout << "Name: " << animation.name << "\n";

		std::cout << "Animation Channels:\n";
		for (auto &channel : animation.channels) {
			std::cout << "=================\nAnimation Channel\n=================\n";
			std::cout << channel << "\n\n";

			std::cout << "::::Sampler::::\n";
			tinygltf::AnimationSampler animationSampler = animation.samplers[channel.sampler];
			std::cout << animationSampler << "\n\n";

			tinygltf::Accessor inputAccessor = model.accessors[animationSampler.input];
			tinygltf::Accessor outputAccessor = model.accessors[animationSampler.output];
			tinygltf::BufferView inputBufferView = model.bufferViews[inputAccessor.bufferView];
			tinygltf::BufferView outputBufferView = model.bufferViews[outputAccessor.bufferView];

			std::cout << "::::Input Accessor::::\n";
			std::cout << inputAccessor << "\n\n";

			std::cout << "::::Input Buffer::::\n";
			std::cout << inputBufferView << "\n\n";

			std::cout << "::::DATA::::\n";
			auto *inBuffData = (float *)(buffer.data.data() + inputBufferView.byteOffset);

			std::cout << "[ ";
			for (unsigned i = 0; i < inputBufferView.byteLength / sizeof(float); i++) {
				std::cout << inBuffData[i] - inBuffData[0];

 				if (i+1 < inputBufferView.byteLength / sizeof(float)) {
					std::cout << ", ";
				}
			}
			std::cout << " ]\n\n";

			std::cout << "::::Input Accessor::::\n";
			std::cout << outputAccessor << "\n\n";

			std::cout << "::::Output Buffer::::\n";
			std::cout << outputBufferView << "\n\n";

			std::cout << "::::DATA::::\n";
			auto *outBuffData = (float *)(buffer.data.data() + outputBufferView.byteOffset);

			std::cout << "[ ";
			for (unsigned i = 0; i < outputBufferView.byteLength / sizeof(float); i++) {
				std::cout << outBuffData[i];
				if (i+1 < outputBufferView.byteLength / sizeof(float)) {
					std::cout << ", ";
				}
			}
			std::cout << " ]\n\n";
		}
	}

//	cge::Entity	bomber1({0, 0, 0}, {0, 0, 0}, 1, bomberModel);
//	cge::Entity	bomber2({0.75, 2, -1}, {0, 0, 0}, 0.5, bomberModel);
//	cge::Entity	cube({1.5, 0.42, 1}, {0, 0, 0}, 0.5, cubeModel);

//	while (gameState != GameState::WANTS_QUIT) {
//		if (processInput(inputManager)) {
//			gameState = GameState::WANTS_QUIT;
//		}
//
//		switch (gameState) {
//			case (GameState::PLAY_GAME): {
//				sounds.PlayMusic(cge::Sounds::Music::Menu);
//
//				if (inputManager.isKeyPressed(SDLK_c)) {
//					std::cout << "Camera:\n" << camera << "\n";
//				}
//
//				bomber1.addRotation({0.0f, 0.025f, 0.0f});
//				bomber2.addRotation({0.05f, 0.0f, 0.0f});
//				cube.addRotation({0.0f, 0.0f, 0.05f});
//
//				shader.start();
//				renderer.prepare();
//				camera.update(shader);
//
//				renderer.render(bomber1);
//				renderer.render(bomber2);
//				renderer.render(cube);
//				shader.end();
//				window.swapBuffers();
//				break;
//			}
//			default:
//			case (GameState::PLAY_MAINMENU):
//				break;
//		}
//	}

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