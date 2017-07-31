#include "Window.hpp"
#include "Loader.hpp"
#include "GLSLProgram.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Maths.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

bool processInput(InputManager &inputManager);
void	openGLError();

std::ostream &operator<<(std::ostream &out, const glm::vec4 &rhs) {
	out << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << " ]";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec3 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec2 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << " }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const Vertex &rhs) {
	out << "{ { " << rhs.position.x << ", " << rhs.position.y << ", " << rhs.position.z << " }, ";
	out << "{ " << rhs.normal.x << ", " << rhs.normal.y << ", " << rhs.normal.z << " }, ";
	out << "{ " << rhs.uv.x << ", " << rhs.uv.y << " } }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs) {
	out << "[ " << rhs[0][0] << ", " << rhs[0][1] << ", " << rhs[0][2] << ", " << rhs[0][3] << " ]\n";
	out << "[ " << rhs[1][0] << ", " << rhs[1][1] << ", " << rhs[1][2] << ", " << rhs[1][3] << " ]\n";
	out << "[ " << rhs[2][0] << ", " << rhs[2][1] << ", " << rhs[2][2] << ", " << rhs[2][3] << " ]\n";
	out << "[ " << rhs[3][0] << ", " << rhs[3][1] << ", " << rhs[3][2] << ", " << rhs[3][3] << " ]\n";

	return out;
}

int main() {
	Window			window("Bomberman", WIDTH, HEIGHT, Window::Flags::VSYNC_ENABLED);
	Loader			loader;
	GLSLProgram		shader;
	Renderer		renderer(shader, &window);
	InputManager	inputManager;

	glm::vec3	normal = { 1.0f, 1.0f, 1.0f };
	std::vector<glm::vec2>	uv = { { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };

	std::vector<Vertex> vertices = {
		{ { -0.5f, 0.5f, -0.5f }, normal, uv[0] },
		{ { -0.5f, -0.5f, -0.5f }, normal, uv[1] },
		{ { 0.5f, -0.5f, -0.5f }, normal, uv[2] },
		{ { 0.5f, 0.5f, -0.5f }, normal, uv[3] },

		{ { -0.5f, 0.5f, 0.5f }, normal, uv[0] },
		{ { -0.5f, -0.5f, 0.5f }, normal, uv[1] },
		{ { 0.5f, -0.5f, 0.5f }, normal, uv[2] },
		{ { 0.5f, 0.5f, 0.5f }, normal, uv[3] },

		{ { 0.5f, 0.5f, -0.5f }, normal, uv[0] },
		{ { 0.5f, -0.5f, -0.5f }, normal, uv[1] },
		{ { 0.5f, -0.5f, 0.5f }, normal, uv[2] },
		{ { 0.5f, 0.5f, 0.5f }, normal, uv[3] },

		{ { -0.5f, 0.5f, -0.5f }, normal, uv[0] },
		{ { -0.5f, -0.5f, -0.5f }, normal, uv[1] },
		{ { -0.5f, -0.5f, 0.5f }, normal, uv[2] },
		{ { -0.5f, 0.5f, 0.5f }, normal, uv[3] },

		{ { -0.5f, 0.5f, 0.5f }, normal, uv[0] },
		{ { -0.5f, 0.5f, -0.5f }, normal, uv[1] },
		{ { 0.5f, 0.5f, -0.5f }, normal, uv[2] },
		{ { 0.5f, 0.5f, 0.5f }, normal, uv[3] },

		{ { -0.5f, -0.5f, 0.5f }, normal, uv[0] },
		{ { -0.5f, -0.5f, -0.5f }, normal, uv[1] },
		{ { 0.5f, -0.5f, -0.5f }, normal, uv[2] },
		{ { 0.5f, -0.5f, 0.5f }, normal, uv[3] }
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

	for (auto &vertex : vertices) {
		std::cout << vertex << "\n";
	}

	Model	model = loader.loadToVAO(vertices, indices, "../image.png");
	Entity	entity(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -5.0f), 1.0f, model);

	Camera camera;

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
		entity.addPosition(glm::vec3(0.0f, 0.0f, -0.01f));
		camera.update(inputManager);


		renderer.prepare();
		shader.start();

		shader.uploadMatrix4f(shader.getUniformLocation("viewMatrix"), Maths::createViewMatrix(camera));
		renderer.render(entity);

		shader.end();
		window.swapBuffers();

		if (GLenum error = glGetError()) std::cout << "Error: " << error << "\n";
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

void	openGLError() {
	GLenum error = glGetError();

	switch (error) {
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			std::cout << "Error: " << error << " Invalid enum\n";
			break;
		case GL_INVALID_VALUE:
			std::cout << "Error: " << error << " Invalid value\n";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "Error: " << error << " Invalid operation\n";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "Error: " << error << "Invalid frambuffer operation\n";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "Error: " << error << " Out of memory\n";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "Error: " << error << " Stack underflow\n";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "Error: " << error << " Stack underflow\n";
			break;
		default:
			std::cout << "Error: " << error << "\n";
	}
}