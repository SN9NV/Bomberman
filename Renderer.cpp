#include "Renderer.hpp"
#include "Maths.hpp"

std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs);

Renderer::Renderer(GLSLProgram &shader, Window *window) {
	init(shader, window);
}

void Renderer::init(GLSLProgram &shader, Window *window) {
	this->_shader = &shader;

	this->_shader->start();

	glm::mat4 projectionMatrix = glm::perspectiveFov<float>(FOV, window->getWidth(), window->getHeight(), NEAR_PLANE, FAR_PLANE);
	this->_shader->uploadMatrix4f(shader.getUniformLocation("projectionMatrix"), projectionMatrix);

	std::cout << "ProjectionMatrix: " << projectionMatrix << "\n";

	this->_shader->end();
}

void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void Renderer::render(Entity &entity) {
	const Model	&model = entity.getModel();

	// Bind the model and texture
	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glm::mat4	transformation = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());

	// Upload the model's transformation matrix
	this->_shader->uploadMatrix4f(this->_shader->getUniformLocation("transformationMatrix"), transformation);

	// Draw the triangles
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);

	// Unbind everything
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}