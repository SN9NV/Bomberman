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
	Player& _player;
	std::vector<std::vector<cge::Entity *>> &_level;

	bool somethingInTheWayX(const glm::vec3 pPos, const glm::vec3 onilPos);
	bool somethingInTheWayY(const glm::vec3 pPos, const glm::vec3 onilPos);

public:
	Onil(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, Player& player, std::vector<std::vector<cge::Entity *>> &level);
	Onil(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBox, Player& player, std::vector<std::vector<cge::Entity *>> &level);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
};


#endif //BOMBERMAN_ONIL_HPP
