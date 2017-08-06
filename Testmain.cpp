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

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

class attrType {
public:
	static constexpr GLuint	POSITION = 0;
	static constexpr GLuint	NORMAL = 1;
	static constexpr GLuint	UV = 2;
	static constexpr GLuint	JOINTS = 3;
	static constexpr GLuint	WEIGHTS = 4;
	static constexpr GLuint UNKNOWN = 5;

	static GLuint convert(const std::string &type) {
		if (type == "POSITION") return attrType::POSITION;
		if (type == "NORMAL") return attrType::NORMAL;
		if (type == "TEXCOORD_0") return attrType::UV;
		if (type == "JOINTS_0") return attrType::JOINTS;
		if (type == "WEIGHTS_0") return attrType::WEIGHTS;

		return attrType::UNKNOWN;
	}
};

std::string GLenumGetString(const GLenum num) {
	switch (num) {
		case GL_UNSIGNED_SHORT:
			return "GL_UNSIGNED_SHORT";
		case GL_UNSIGNED_INT:
			return "GL_UNSIGNED_INT";
		case GL_UNSIGNED_BYTE:
			return "GL_UNSIGNED_BYTE";
		case GL_ARRAY_BUFFER:
			return "GL_ARRAY_BUFFER";
		case GL_ELEMENT_ARRAY_BUFFER:
			return "GL_ELEMENT_ARRAY_BUFFER";
		case GL_TRIANGLES:
			return "GL_TRIANGLES";
		case GL_TRIANGLE_STRIP:
			return "GL_TRIANGLE_STRIP";
		case GL_TRIANGLE_FAN:
			return "GL_TRIANGLE_FAN";
		case GL_POINTS:
			return "GL_POINTS";
		case GL_LINE:
			return "GL_LINE";
		case GL_LINE_LOOP:
			return "GL_LINE_LOOP";
		default:
			return "*** UNKNOWN ***";
	}
}

std::vector<GLuint> gBuffers;

void	drawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh) {
	for (auto &primitive : mesh.primitives) {
		if (primitive.indices < 0)
			continue;

		for (auto &attr : primitive.attributes) {
			const auto &accessor = model.accessors[attr.second];

			glBindBuffer(GL_ARRAY_BUFFER, gBuffers[accessor.bufferView]);

			GLint size;

			switch (accessor.type) {
				case TINYGLTF_TYPE_VEC2:
					size = 2;
					break;
				case TINYGLTF_TYPE_VEC3:
					size = 3;
					break;
				case TINYGLTF_TYPE_VEC4:
					size = 4;
					break;
				default:
					size = 1;
			}

			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
				glVertexAttribPointer(
						index,
						size,
						(GLenum)accessor.componentType,
						(GLboolean)((accessor.normalized) ? GL_TRUE : GL_FALSE),
						(GLsizei)model.bufferViews[accessor.bufferView].byteStride,
						BUFFER_OFFSET(accessor.byteOffset)
				);

				glEnableVertexAttribArray(index);
			}
		}

		const auto &indexAssessor = model.accessors[primitive.indices];
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gBuffers[indexAssessor.bufferView]);

		glDrawElements((GLenum)primitive.mode, (GLsizei)indexAssessor.count, (GLenum)indexAssessor.componentType,
			BUFFER_OFFSET(indexAssessor.byteOffset));

		for (auto &attr : primitive.attributes) {
			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
				glDisableVertexAttribArray(index);
			}
		}
	}
}

void	setupMeshState(tinygltf::Model &model) {
	for (const auto &view : model.bufferViews) {
		if (view.target == 0) {
			continue;
		}

		const tinygltf::Buffer &buffer = model.buffers[view.buffer];
		std::cout << view.buffer << "\n";

		GLuint vboID = 0;
		glGenBuffers(1, &vboID);
		glBindBuffer((GLenum)view.target, vboID);
		glBufferData((GLenum)view.target, view.byteLength, buffer.data.data() + view.byteOffset, GL_STATIC_DRAW);
		glBindBuffer((GLenum)view.target, 0);

		gBuffers.push_back(vboID);
	}
}

void	drawNode(tinygltf::Model &model, const tinygltf::Node &node) {
	drawMesh(model, model.meshes[(node.mesh >= 0) ? node.mesh : 0]);
}

void	drawModel(tinygltf::Model &model) {
	const tinygltf::Scene &scene = model.scenes[model.defaultScene];
	for (auto &node : scene.nodes) {
		drawNode(model, model.nodes[node]);
	}
}

bool	processInput(InputManager &inputManager);

int main() {
	Window			window("Bomberman", WIDTH, HEIGHT, Window::Flags::VSYNC_ENABLED);
	GLSLProgram		shader("../Testvertex.glsl", "../Textfragment.glsl", { "view" });
	InputManager	inputManager;

	tinygltf::Model model;
	tinygltf::TinyGLTF glTFLoader;
	std::string err;

	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../resources/moddels/bomner2.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../cube.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../unwrappedCube.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../doubleCube.glb");
//	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../companion.glb");

	if (!err.empty()) {
		std::cout << "Err: " << err << "\n";
	}

	if (!ret) {
		std::cout << "Failed to parse glTF\n";
		return -1;
	}

	Camera camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), window);

	enum GameState {
		PLAY,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY;
	setupMeshState(model);

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState ::WANTS_QUIT;
		}

		if (inputManager.isKeyPressed(SDLK_c)) {
			std::cout << "Camera:\n" << camera << "\n";
		}

		shader.start();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		camera.update(inputManager, shader);

		drawModel(model);

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

