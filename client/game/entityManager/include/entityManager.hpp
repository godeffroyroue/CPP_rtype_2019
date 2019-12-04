/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EntityManager
*/

#ifndef EntityManager_HPP_
#define EntityManager_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "entity.hpp"
#include "EntityLoader.hpp"

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        void loadEntity();
        void translanteEntity(IEntity* tmp);
        void addEntity(int id, std::string uid, sf::Vector2f pos);
        void removeEntity(std::string uid);
        std::vector<std::shared_ptr<Entity>> getCurrent() const;
    private:
        std::vector<std::shared_ptr<Entity>> all;
        std::vector<std::shared_ptr<Entity>> current;
};

#endif /* !EntityManager_HPP_ */
