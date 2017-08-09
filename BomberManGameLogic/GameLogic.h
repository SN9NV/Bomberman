//
// Created by Robert JONES on 2017/08/08.
//

#ifndef BOMBERMAN_GAMELOGIC_H
#define BOMBERMAN_GAMELOGIC_H

#include "../io/Window.hpp"
#include "../loaders/Loader.hpp"
#include "Player.hpp"


void runLevel(Player *player,std::string levelPath, cge::Loader &loader, cge::Window	window);

#endif //BOMBERMAN_GAMELOGIC_H
