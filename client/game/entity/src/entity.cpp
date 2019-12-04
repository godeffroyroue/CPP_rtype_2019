/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** entity
*/

#include "entity.hpp"

Entity::Entity()
{
}

// Entity::Entity(std::shared_ptr<SFMLGraphics> graph, std::shared_ptr<Spec> spec, std::shared_ptr<SFMLPhysic> physic)
// {
//     this->_graph = graph;
//     this->_physic = physic;
//     this->_spec = spec;
// }

Entity::~Entity()
{
}

void Entity::setGraph(sf::Texture texture, sf::Sprite sprite, int offset)
{
    this->_graph =  std::shared_ptr<SFMLGraphics>(new SFMLGraphics(texture, sprite, offset));
}

void Entity::setGraph(std::shared_ptr<SFMLGraphics> graph)
{
    this->_graph =  std::shared_ptr<SFMLGraphics>(new SFMLGraphics(graph));
}

void Entity::setPhysic(sf::Vector2f move, sf::Vector2f pos)
{
    this->_physic = std::shared_ptr<SFMLPhysic>(new SFMLPhysic(move, pos));
}

void Entity::setPhysic(std::shared_ptr<SFMLPhysic> physic)
{
    this->_physic = std::shared_ptr<SFMLPhysic>(new SFMLPhysic(physic));
}


void Entity::setSpec(int id, std::string uid, int damage, bool enemy, int health, sf::Vector2f size, int idShoot, int freqShoot)
{
    this->_spec = std::shared_ptr<Spec>(new Spec(id, uid, damage, enemy, health, size, idShoot, freqShoot));
}

void Entity::setSpec(std::shared_ptr<Spec> spec)
{
    this->_spec = std::shared_ptr<Spec>(new Spec(spec));
}


std::shared_ptr<SFMLGraphics> Entity::getGraph() const
{
    return (this->_graph);
}

std::shared_ptr<Spec> Entity::getSpec() const
{
    return (this->_spec);
}

std::shared_ptr<SFMLPhysic> Entity::getPhysic() const
{
    return (this->_physic);
}

