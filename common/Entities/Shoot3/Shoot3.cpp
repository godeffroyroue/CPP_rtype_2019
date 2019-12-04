/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Shoot3
*/

#include "Shoot3.hpp"

Shoot3::Shoot3() : AEntity(1, 11, 20, true, std::vector<float>{34, 20}, std::vector<float>{0, 0}, std::vector<float>{-1.5, 0}, "client/game/ressources/entitySprite/shoot/shoot3/shoot3.png", 4, -1, -1)
{
}

Shoot3::~Shoot3()
{
}

extern "C" IEntity *create() {
    return (new Shoot3());
}
