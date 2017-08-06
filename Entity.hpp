#ifndef NEW_ENTITY_HPP
#define NEW_ENTITY_HPP

#include <glm/glm.hpp>
#include "Model.hpp"
#include "GLSLProgram.hpp"

class Entity {
public:
	Entity() = default;
	~Entity() = default;

	Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, const Model &model);

	void		addPosition(const glm::vec3 &delta);
	void		setPosition(const glm::vec3 &position);
	void		addRotation(const glm::vec3 &delta);
	void		setRotation(const glm::vec3 &rotation);

	Model		&getModel();
	glm::vec3	getPosition() const;
	glm::vec3	getRotation() const;
	float 		getScale() const;

	void		updateTransformation(const GLSLProgram &shader);

private:
	Model		_model;
	glm::vec3	_position;
	glm::vec3	_rotation;
	float 		_scale;
	glm::mat4	_transformation;
	GLint		_transformationLocation;

	bool		_needsTransformationUpdate;
};


#endif //NEW_ENTITY_HPP
