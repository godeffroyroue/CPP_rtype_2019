/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player1
*/

#include "Player1.hpp"

Player1::Player1() : AEntity(100, 1, 2, false, std::vector<float>{60, 31}, std::vector<float>{0, 0}, std::vector<float>{0, 0}, "client/game/ressources/entitySprite/player/player1/player1.png", 1, 13, 1)
{
}

Player1::~Player1()
{
}

extern "C" IEntity *create() {
    return (new Player1());
}