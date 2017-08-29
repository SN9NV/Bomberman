//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_ONIL_HPP
#define BOMBERMAN_ONIL_HPP

#include "Being.hpp"
#include "Player.hpp"

class Onil : public Being {
private:
	int _changeDir;
	const Player& _player;
	std::vector<std::vector<cge::Entity *>> &_level;

	bool somethingInTheWayX(const glm::vec3 &pPos, const glm::vec3 &onilPos);
	bool somethingInTheWayY(const glm::vec3 &pPos, const glm::vec3 &onilPos);

public:
	Onil(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, const Player& player, std::vector<std::vector<cge::Entity *>> &level, float hitBox = 0.5f);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) override;

protected:
	void	_setEffects() override;
};


#endif //BOMBERMAN_ONIL_HPP
