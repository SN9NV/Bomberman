#ifndef NEW_ENTITY_HPP
#define NEW_ENTITY_HPP

#include <glm/glm.hpp>
#include "Model.hpp"
#include "GLSLProgram.hpp"
#include "InputManager.hpp"

namespace cge {
	class Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;

		Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model);

		virtual void	update(const InputManager &input, unsigned lastFrameTime);
		void			addPosition(const glm::vec3 &delta);
		void			setPosition(const glm::vec3 &position);
		void			addRotation(const glm::vec3 &delta);
		void			setRotation(const glm::vec3 &rotation);

		Model		&getModel();
		glm::vec3	getPosition() const;
		glm::vec3	getRotation() const;
		float 		getScale() const;

	protected:
		Model		&_model;
		glm::vec3	_position;
		glm::vec3	_rotation;
		float 		_scale;
		glm::mat4	_transformation;
		GLint		_transformationLocation;

		bool		_needsTransformationUpdate;
	};
}

#endif //NEW_ENTITY_HPP
