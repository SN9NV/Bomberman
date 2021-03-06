#ifndef NEW_RENDERER_HPP
#define NEW_RENDERER_HPP

#include <glm/glm.hpp>
#include "GLSLProgram.hpp"
#include "../entites/Entity.hpp"
#include "../io/Window.hpp"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

namespace cge {
	class Renderer {
	public:
		class attrType {
		public:
			static constexpr GLuint POSITION = 0;
			static constexpr GLuint NORMAL = 1;
			static constexpr GLuint UV = 2;
			static constexpr GLuint JOINTS = 3;
			static constexpr GLuint WEIGHTS = 4;
			static constexpr GLuint UNKNOWN = 5;

			static GLuint convert(const std::string &type);
		};

		Renderer() = default;
		Renderer(GLSLProgram &shader);

		~Renderer() = default;

		void	prepare() const;
		void	render(Entity &entity) const;
		void	render(std::vector<cge::Entity *> &entities);

		/// Upload uniforms
		void	uploadIsAnimated(bool isAnimated) const;
		void	uploadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;
		void	uploadTransformation(const glm::mat4 &transformation) const;
		void	uploadView(const glm::mat4 &view) const;

	private:
		const GLSLProgram &_shader;

		void drawMesh(const tinygltf::Model &model, const tinygltf::Mesh &mesh, const std::vector<GLuint> &vboMap) const;

		/// Entity shader uniforms
		GLint	_uniformIsAnimated;
		GLint	_uniformJointTransforms;
		GLint	_uniformTransformation;
		GLint	_uniformView;
	};
}

#endif //NEW_RENDERER_HPP
