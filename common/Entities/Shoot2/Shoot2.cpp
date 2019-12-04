/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Shoot2
*/

#include "Shoot2.hpp"

Shoot2::Shoot2() : AEntity(1, 10, 15, true, std::vector<float>{32, 31}, std::vector<float>{0, 0}, std::vector<float>{-2, 1}, "client/game/ressources/entitySprite/shoot/shoot2/shoot2.png", 4, -1, -1)
{
}

Shoot2::~Shoot2()
{
}

extern "C" IEntity *create() {
    return (new Shoot2());
}
