#ifndef NEW_CAMERA_HPP
#define NEW_CAMERA_HPP

#include <glm/glm.hpp>

#include "InputManager.hpp"
#include "GLSLProgram.hpp"

class Camera {
public:
    Camera() = default;
    ~Camera() = default;

	Camera(const glm::vec3 &position, const glm::vec3 &rotation);

	void		setPosition(const glm::vec3 &position);
	void		setRotation(const glm::vec3 &rotation);
	glm::vec3	getPosition() const;
	glm::vec3	getRotation() const;

	void	update(const InputManager &inputManager, const GLSLProgram &shader);

private:
	glm::vec3	_position;
	glm::vec3	_rotation;
	bool 		_needsUpdate;
};


#endif //NEW_CAMERA_HPP
