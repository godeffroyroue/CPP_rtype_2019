/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player4
*/

#include "Player4.hpp"

Player4::Player4() : AEntity(100, 4, 2, false, std::vector<float>{60, 31}, std::vector<float>{0, 0}, std::vector<float>{0, 0}, "client/game/ressources/entitySprite/player/player4/player4.png", 1, 13, 1)
{
}

Player4::~Player4()
{
}

extern "C" IEntity *create() {
    return (new Player4());
}