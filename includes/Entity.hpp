#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Model.hpp"
#include <glm/glm.hpp>

class Entity
{
	public:
		Entity();
		Entity(Model &model, glm::vec3 &position, glm::vec3 &rotation, float scale);
		Entity(Entity &entity);
		~Entity();

		Entity &operator=(Entity &rhs);

		init(Model &model, glm::vec3 &position, glm::vec3 &rotation, float scale);

		void	addPosition(glm::vec3 &delta);
		void	addRotation(glm::vec3 &delta);
		void	addScale(float delta);

		void	setModel(Model &model);
		void	setPosition(glm::vec3 &position);
		void	setRotation(glm::vec3 &rotation);
		void	setScale(float scale);

		Model		model(void) const;
		glm::vec3	position(void) const;
		glm::vec3	rotation(void) const;
		float		scale(void) const;

	private:
		Model		_model;
		glm::vec3	_position;
		glm::vec3	_rotation;
		float		_scale;
};

#endif // ENTITY_HPP
