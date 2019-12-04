/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Shoot1
*/

#include "Shoot1.hpp"

Shoot1::Shoot1() : AEntity(1, 9, 10, true, std::vector<float>{34, 34}, std::vector<float>{0, 0}, std::vector<float>{-3, 0}, "client/game/ressources/entitySprite/shoot/shoot1/shoot1.png", 3,  -1, -1)
{
}

Shoot1::~Shoot1()
{
}

extern "C" IEntity *create() {
    return (new Shoot1());
}
