/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Shoot4
*/

#include "Shoot4.hpp"

Shoot4::Shoot4() : AEntity(1, 12, 50, true, std::vector<float>{25, 25}, std::vector<float>{200, 200}, std::vector<float>{-2, 0}, "client/game/ressources/entitySprite/shoot/shoot4/shoot4.png", 9, -1, -1)
{
}

Shoot4::~Shoot4()
{
}

extern "C" IEntity *create() {
    return (new Shoot4());
}
