/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Mechant1
*/

#include "Mechant1.hpp"

Mechant1::Mechant1() : AEntity(100, 5, 50, true, std::vector<float>{100, 85}, std::vector<float>{0, 0}, std::vector<float>{-2, 0}, "client/game/ressources/entitySprite/mechant/mechant1/mechant1.png", 3, 9, 1.5)
{
}

Mechant1::~Mechant1()
{
}

extern "C" IEntity *create() {
    return (new Mechant1());
}