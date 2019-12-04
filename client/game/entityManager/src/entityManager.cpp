/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** entityManagement
*/

#include "entityManager.hpp"

EntityManager::EntityManager()
{
    loadEntity();
}

EntityManager::~EntityManager()
{
}

void EntityManager::translanteEntity(IEntity* tmp)
{
    std::shared_ptr<Entity> save = std::shared_ptr<Entity>(new Entity());
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Vector2f move;

    if (!texture.loadFromFile(tmp->getTexturePath()))
        return;
    sprite.setTexture(texture);
    save->setGraph(texture, sprite, tmp->getOffset());
    size.x = tmp->getSize()[0];
    size.y = tmp->getSize()[1];
    save->getGraph()->setRect(size);
    save->setSpec(tmp->getId(), "", tmp->getDamage(), tmp->getEnemy(), tmp->getHealth(), size, tmp->getIdShoot(), tmp->getFreqShoot());
    pos.x = tmp->getPos()[0];
    pos.y = tmp->getPos()[1];
    move.x = tmp->getMove()[0];
    move.y = tmp->getMove()[1];
    save->setPhysic(move, pos);
    save->getPhysic()->setSize(size.x, size.y);
    this->all.push_back(save);
}

void EntityManager::loadEntity()
{
    std::cout << "loading entity" << std::endl;
    std::shared_ptr<EntityLoader> load = std::shared_ptr<EntityLoader>(new EntityLoader());
    load->getEntityVector();
    std::vector<void *> hdl = load->getHandleList();
    std::vector<IEntity*> tmp;
    for (void * h : hdl)
        translanteEntity(load->getInstanceWithHandle(h));
}

void EntityManager::removeEntity(std::string uid)
{
    for (size_t i = 0; i < this->current.size(); i++){
        if (current[i]->getSpec()->getUid() == uid){
            this->current.erase(this->current.begin() + i);
            return;
        }
    }
}

std::vector<std::shared_ptr<Entity>> EntityManager::getCurrent() const
{
    return (this->current);
}

void EntityManager::addEntity(int id, std::string uid, sf::Vector2f pos)
{
    for (std::shared_ptr<Entity> ent : this->all){
        if (ent->getSpec()->getId() == id){
            std::shared_ptr<Entity> added = std::shared_ptr<Entity>(new Entity());
            added->setSpec(ent->getSpec());
            added->setPhysic(ent->getPhysic());
            added->setGraph(ent->getGraph());
            added->getSpec()->setUid(uid);
            added->getPhysic()->setPos(pos.x, pos.y);
            added->getGraph()->setPosition(pos.x, pos.y);
            this->current.push_back(added);
            return;
        }
    }
}
