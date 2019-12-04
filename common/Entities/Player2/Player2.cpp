/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player2
*/

#include "Player2.hpp"

Player2::Player2() : AEntity(100, 2, 2, false, std::vector<float>{60, 31}, std::vector<float>{0, 0}, std::vector<float>{0, 0}, "client/game/ressources/entitySprite/player/player2/player2.png", 1, 13, 1)
{
}

Player2::~Player2()
{
}

extern "C" IEntity *create() {
    return (new Player2());
}