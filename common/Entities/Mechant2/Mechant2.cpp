/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Mechant2
*/

#include "Mechant2.hpp"

Mechant2::Mechant2() : AEntity(200, 6, 50, true, std::vector<float>{117, 120}, std::vector<float>{0, 0}, std::vector<float>{-1.5, 0}, "client/game/ressources/entitySprite/mechant/mechant2/mechant2.png", 5, 10, 2)
{
}

Mechant2::~Mechant2()
{
}

extern "C" IEntity *create() {
    return (new Mechant2());
}