#ifndef NEW_RENDERER_HPP
#define NEW_RENDERER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLSLProgram.hpp"
#include "Entity.hpp"
#include "Window.hpp"

class Renderer {
public:
	static constexpr float	FOV = 70.0f;
	static constexpr float	NEAR_PLANE = 0.1f;
	static constexpr float	FAR_PLANE = 1000.0f;

	Renderer() = default;
	~Renderer() = default;

	explicit Renderer(GLSLProgram &shader, Window *window);

	void	init(GLSLProgram &shader, Window *window);
	void	prepare();
	void	render(Entity &entity);

private:
	glm::mat4	_projectionMatrix;
	GLSLProgram	*_shader;
};


#endif //NEW_RENDERER_HPP
