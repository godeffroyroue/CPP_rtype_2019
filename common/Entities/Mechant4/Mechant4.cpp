/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Mechant4
*/

#include "Mechant4.hpp"

Mechant4::Mechant4() : AEntity(500, 8, 50, true, std::vector<float>{312.5, 400}, std::vector<float>{0, 0}, std::vector<float>{-1, 0}, "client/game/ressources/entitySprite/mechant/mechant4/mechant4.png", 4, 12, 1)
{
}

Mechant4::~Mechant4()
{
}

extern "C" IEntity *create() {
    return (new Mechant4());
}