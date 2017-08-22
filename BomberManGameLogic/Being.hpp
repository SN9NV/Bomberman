//
// Created by rojones on 2017/08/07.
//

#ifndef BOMBERMAN_BEING_HPP
#define BOMBERMAN_BEING_HPP


#include "../entites/Entity.hpp"
#include "../io/InputManager.hpp"
#include "../rendering/Renderer.hpp"
#include "Bomb.hpp"

class Being : public cge::Entity
{
protected:
	float _speed;
	glm::vec3 _n_moveDir;
	size_t _maxBomb;
	std::vector<Bomb *> _bombs;
	bool _plaseBomb;
	int	_damage;
	unsigned _deathTimeout;
	bool _alive;
public:
	bool isAlive() const;

	void setAlive(bool _alive);

	int getDamage() const;

	void setDamage(int _damage);

	void setPlaseBomb(bool _plaseBomb);

	const glm::vec3 &get_n_moveDir() const;

	bool isPlaceBomb() const;

	void placeBomb(Bomb *bomb);

	bool checkBombDeterNation(Bomb *bomb);

	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
		  float speed);

	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox,
		  float speed);

	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius,
		  float _speed, int _damage);

	Being() = default;

	virtual bool	update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) override;

	void setDirection();

	void setMoveDir(glm::vec3 newDir);

	float getDirAngle();

	void setSpeed(const float speed);
	float getSpeed() const;
};


#endif //BOMBERMAN_BEING_HPP
