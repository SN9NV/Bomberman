#ifndef NEW_CAMERA_HPP
#define NEW_CAMERA_HPP

#include <glm/glm.hpp>

#include "../io/InputManager.hpp"
#include "../rendering/GLSLProgram.hpp"
#include "../io/Window.hpp"

namespace cge {
	class Camera {
	public:
		static constexpr float		FOV			= 70.0f;
		static constexpr float		NEAR_PLANE	= 0.01f;
		static constexpr float		FAR_PLANE	= 1000.0f;

		Camera() = default;

		~Camera() = default;

		Camera(const glm::vec3 &position, const glm::vec3 &rotation, const Window &window);
		void		setPosition(const glm::vec3 &position);
		void		addPosition(const glm::vec3 &delta);
		void		setRotation(const glm::vec3 &rotation);
		void		addRotation(const glm::vec3 &delta);
		glm::vec3	getPosition() const;
		glm::vec3	getRotation() const;
		glm::mat4	getProjectionMatrix() const;
		glm::mat4	getViewMatrix() const;

		void	update(const GLSLProgram &shader, bool printCameraChange = false);
	private:
		glm::vec3	_position;
		glm::vec3	_rotation;
		glm::mat4	_projectionMatrix;
		glm::mat4	_viewMatrix;

		bool 		_needsUpdate;
	};
}

std::ostream &operator<<(std::ostream &out, const cge::Camera &rhs);


#endif //NEW_CAMERA_HPP
