/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "specification.hpp"
#include "SFMLGraphics.hpp"
#include "SFMLPhysic.hpp"
#include <memory>

class Entity
{
    public:
        Entity();
        ~Entity();
        void setGraph(sf::Texture texture, sf::Sprite sprite, int offset);
        void setGraph(std::shared_ptr<SFMLGraphics> graph);
        void setSpec(int id, std::string uid, int damage, bool enemy, int health, sf::Vector2f size, int idShoot, int freqShoot);
        void setSpec(std::shared_ptr<Spec> spec);
        void setPhysic(sf::Vector2f move, sf::Vector2f pos);
        void setPhysic(std::shared_ptr<SFMLPhysic> physic);
        std::shared_ptr<SFMLGraphics> getGraph() const;
        std::shared_ptr<Spec> getSpec() const;
        std::shared_ptr<SFMLPhysic> getPhysic() const;
    private:
        std::shared_ptr<SFMLGraphics> _graph;
        std::shared_ptr<Spec> _spec;
        std::shared_ptr<SFMLPhysic> _physic;
};

#endif /* !ENTITY_HPP_ */
