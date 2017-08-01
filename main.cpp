#include "Window.hpp"
#include "Loader.hpp"
#include "GLSLProgram.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Maths.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

bool	processInput(InputManager &inputManager);

int main() {
	Window			window("Bomberman", WIDTH, HEIGHT, Window::Flags::VSYNC_ENABLED);
	Loader			loader;
	GLSLProgram		shader;
	Renderer		renderer(shader, window);
	InputManager	inputManager;

	glm::vec3	normal = { 1.0f, 1.0f, 1.0f };
	std::vector<glm::vec2>	uv = { { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };

	std::vector<Vertex> vertices = {
		{ { -0.5f, 0.5f, -0.5f }, uv[0], normal },
		{ { -0.5f, -0.5f, -0.5f }, uv[1], normal },
		{ { 0.5f, -0.5f, -0.5f }, uv[2], normal },
		{ { 0.5f, 0.5f, -0.5f }, uv[3], normal },

		{ { -0.5f, 0.5f, 0.5f }, uv[0], normal },
		{ { -0.5f, -0.5f, 0.5f }, uv[1], normal },
		{ { 0.5f, -0.5f, 0.5f }, uv[2], normal },
		{ { 0.5f, 0.5f, 0.5f }, uv[3], normal },

		{ { 0.5f, 0.5f, -0.5f }, uv[0], normal },
		{ { 0.5f, -0.5f, -0.5f }, uv[1], normal },
		{ { 0.5f, -0.5f, 0.5f }, uv[2], normal },
		{ { 0.5f, 0.5f, 0.5f }, uv[3], normal },

		{ { -0.5f, 0.5f, -0.5f }, uv[0], normal },
		{ { -0.5f, -0.5f, -0.5f }, uv[1], normal },
		{ { -0.5f, -0.5f, 0.5f }, uv[2], normal },
		{ { -0.5f, 0.5f, 0.5f }, uv[3], normal },

		{ { -0.5f, 0.5f, 0.5f }, uv[0], normal },
		{ { -0.5f, 0.5f, -0.5f }, uv[1], normal },
		{ { 0.5f, 0.5f, -0.5f }, uv[2], normal },
		{ { 0.5f, 0.5f, 0.5f }, uv[3], normal },

		{ { -0.5f, -0.5f, 0.5f }, uv[0], normal },
		{ { -0.5f, -0.5f, -0.5f }, uv[1], normal },
		{ { 0.5f, -0.5f, -0.5f }, uv[2], normal },
		{ { 0.5f, -0.5f, 0.5f }, uv[3], normal }
	};

	std::vector<unsigned>	indices = {
		0, 1, 3,
		3, 1, 2,
		4, 5, 7,
		7, 5, 6,
		8, 9, 11,
		11, 9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22
	};

	std::vector<unsigned>	indices2 = {
			0, 1, 3,
			3, 1, 2,
			4, 5, 7,
			7, 5, 6,
			8, 9, 11,
			11, 9, 10,
			12, 13, 15,
			15, 13, 14,
			16, 17, 19,
			19, 17, 18
	};

	Model	model = loader.loadToVAO(vertices, indices, "../image.png");
	Model	model2 = loader.loadToVAO(vertices, indices2, "../image2.png");
	Entity	entity(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -5.0f), 1.0f, model);

	std::vector<Entity>		entities {
			Entity(glm::vec3(5.0f, 3.0f, -10.0f), glm::vec3(0, 0, 0), 1.0f, model2),
			Entity(glm::vec3(2.5f, 3.0f, -10.0f), glm::vec3(0, 0, 0), 1.0f, model),
			Entity(glm::vec3(0.0f, 3.0f, -10.0f), glm::vec3(0, 0, 0), 1.0f, model2),
			Entity(glm::vec3(-2.5f, 3.0f, -10.0f), glm::vec3(0, 0, 0), 1.0f, model),
			Entity(glm::vec3(-5.0f, 3.0f, -10.0f), glm::vec3(0, 0, 0), 1.0f, model2)
	};

	Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	enum GameState {
		PLAY,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY;

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState ::WANTS_QUIT;
		}

		entity.addRotation(glm::vec3(0.005f, 0.005f, 0.0f));
//		entity.addPosition(glm::vec3(0.0f, 0.0f, -0.01f));

		renderer.prepare();
		shader.start();

		camera.update(inputManager, shader);
		renderer.render(entity);

		float rotation = 0.0f;
		for (auto &cEntity : entities) {
			rotation += 0.05f;
			cEntity.addRotation(glm::vec3(rotation, rotation, 0.0f));
			renderer.render(cEntity);
		}

		shader.end();
		window.swapBuffers();
	}

	return 0;
}

bool processInput(InputManager &inputManager) {
	SDL_Event	event;

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

