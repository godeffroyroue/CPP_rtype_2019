/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Mechant3
*/

#include "Mechant3.hpp"

Mechant3::Mechant3() : AEntity(300, 7, 50, true, std::vector<float>{110, 110}, std::vector<float>{0, 0}, std::vector<float>{-1, -0.2}, "client/game/ressources/entitySprite/mechant/mechant3/mechant3.png", 5, 11, 3)
{
}

Mechant3::~Mechant3()
{
}

extern "C" IEntity *create() {
    return (new Mechant3());
}