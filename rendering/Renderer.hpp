#ifndef NEW_RENDERER_HPP
#define NEW_RENDERER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLSLProgram.hpp"
#include "../entites/Entity.hpp"
#include "../io/Window.hpp"

namespace cge {
	class Renderer {
	public:
		Renderer() = default;
		Renderer(GLSLProgram &shader);

		~Renderer() = default;

		void	prepare() const;
		void	render(Entity &entity) const;
		void	render(std::vector<cge::Entity> &entities) const;

		/// Upload uniforms
		void	uploadIsAnimated(bool isAnimated) const;
		void	uploadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;
		void	uploadTransformation(const glm::mat4 &transformation) const;
		void	uploadView(const glm::mat4 &view) const;

	private:
		const GLSLProgram &_shader;

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

		void drawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh, std::vector<GLuint> &vboMap) const;

		/// Uniform variables
		static constexpr unsigned __MAX_JOINTS = 50;

		/// Entity shader uniforms
		GLint	_uniformIsAnimated;
		GLint	_uniformJointTransforms[__MAX_JOINTS];
		GLint	_uniformTransformation;
		GLint	_uniformView;
	};
}

#endif //NEW_RENDERER_HPP
