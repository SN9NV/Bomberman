#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

<<<<<<< HEAD
constexpr GLint WIDTH = 1024;
constexpr GLint HEIGHT = 768;

=======
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae
int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x Antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For OSX
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // No old OpenGL

<<<<<<< HEAD
	GLFWwindow	*window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);
=======
	GLFWwindow	*window;
	window = glfwCreateWindow(1024, 768, "Test", nullptr, nullptr);
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae

	if (window == nullptr) {
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return -1;
	}

<<<<<<< HEAD
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = GL_TRUE;
=======
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true;

	GLuint	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

<<<<<<< HEAD
	glViewport(0, 0, screenWidth, screenHeight);

	GLuint	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

=======
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		// Draw something
<<<<<<< HEAD
		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   0,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,			// size
		   GL_FLOAT,	// type
		   GL_FALSE,	// normalized?
		   0,			// stride
		   nullptr		// array buffer offset
=======
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
<<<<<<< HEAD
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	glfwTerminate();

	return 0;
=======
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
>>>>>>> 011cc7c73b3df58103677b065d0b44e8a2db04ae
}
