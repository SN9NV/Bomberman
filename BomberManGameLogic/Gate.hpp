//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_GATE_HPP
#define BOMBERMAN_GATE_HPP


#include "../entites/Entity.hpp"

class Gate : public cge::Entity {
private:
	bool	_active;
	bool	_damage;
	size_t	_damageCycles;

	//void	_setEffects() override;

public:
	Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius = 0.5f);
	virtual ~Gate() = default;

	void activate();
	bool isActive() const;

	bool isDamage() const;
	void setDamage(bool damage);
	void damage(size_t damageCycles);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
};


#endif //BOMBERMAN_GATE_HPP
