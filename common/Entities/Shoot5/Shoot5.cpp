/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Shoot5
*/

#include "Shoot5.hpp"

Shoot5::Shoot5() : AEntity(1, 13, 500, false, std::vector<float>{39, 20}, std::vector<float>{0, 0}, std::vector<float>{2, 0}, "client/game/ressources/entitySprite/shoot/shoot5/shoot5.png", 4, -1, -1)
{
}

Shoot5::~Shoot5()
{
}

extern "C" IEntity *create() {
    return (new Shoot5());
}
