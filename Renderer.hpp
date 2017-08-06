#ifndef NEW_RENDERER_HPP
#define NEW_RENDERER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLSLProgram.hpp"
#include "Entity.hpp"
#include "Window.hpp"

class Renderer {
public:
	Renderer() = default;
	~Renderer() = default;

	Renderer(const GLSLProgram &shader);

	void	prepare() const;
	void	render(Entity &entity) const;

private:
	const	GLSLProgram	&_shader;

	class attrType {
	public:
		static constexpr GLuint	POSITION = 0;
		static constexpr GLuint	NORMAL = 1;
		static constexpr GLuint	UV = 2;
		static constexpr GLuint	JOINTS = 3;
		static constexpr GLuint	WEIGHTS = 4;
		static constexpr GLuint UNKNOWN = 5;

		static GLuint convert(const std::string &type);
	};

	void	drawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh, std::vector<GLuint> &vboMap) const;
};


#endif //NEW_RENDERER_HPP
