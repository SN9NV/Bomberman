//
// Created by rojones on 2017/08/26.
//

#include "WallPass.hpp"

WallPass::WallPass(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
				   cge::Loader &loader, float hitBoxRadius) : PowerUPAbstract(position, rotation,
																								  scale, model, loader,
																								  hitBoxRadius)
																				   {}

void WallPass::Powerup(Player &player)
{
	_previusState = player.isWallPass();
	player.setWallPass(true);
}

void WallPass::Reverse(Player &player)
{
	player.setWallPass(_previusState);
}
