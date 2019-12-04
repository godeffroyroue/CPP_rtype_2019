/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player3
*/

#include "Player3.hpp"

Player3::Player3() : AEntity(100, 3, 2, false, std::vector<float>{60, 31}, std::vector<float>{0, 0}, std::vector<float>{0, 0}, "client/game/ressources/entitySprite/player/player3/player3.png", 1, 13, 1)
{
}

Player3::~Player3()
{
}

extern "C" IEntity *create() {
    return (new Player3());
}