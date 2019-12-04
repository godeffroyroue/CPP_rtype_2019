/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** specification
*/

#include "specification.hpp"

Spec::Spec(int id, std::string uid, int damage, bool enemy, int health, sf::Vector2f size, int idShoot, int freqShoot)
{
    this->_id = id;
    this->_uid = uid;
    this->_damage = damage;
    this->_enemy = enemy;
    this->_health = health;
    this->_dead = false;
    this->_size = size;
    this->unbreak = false;
    this->duration = 0;
    this->_idShoot = idShoot;
    this->_freqShoot = freqShoot * 5;
    this->fire_duration = 0;
    this->fire = false;
}

Spec::Spec(std::shared_ptr<Spec> &p2)
{
    this->_id = p2->_id;
    this->_uid = p2->_uid;
    this->_damage = p2->_damage;
    this->_enemy = p2->_enemy;
    this->_health = p2->_health;
    this->_dead = false;
    this->_size = p2->_size;
    this->unbreak = false;
    this->duration = 0;
    this->_idShoot = p2->_idShoot;
    this->_freqShoot = p2->_freqShoot;
    this->fire_duration = 0;
    this->fire = false;
}


Spec::~Spec()
{
}

void Spec::setBreak(bool state)
{
    this->unbreak = state;
}

void Spec::addDuration()
{
    this->duration++;
    if (this->duration == TIME){
        this->duration = 0;
        this->unbreak = false;
    }
}

bool Spec::getFire() const
{
    return (this->fire);
}

int Spec::getIdShoot() const
{
    return (this->_idShoot);
}

void Spec::setFire(bool state)
{
    this->fire = state;
}

void Spec::addFire()
{
    this->fire_duration++;
    if (this->fire_duration == this->_freqShoot){
        this->fire_duration = 0;
        this->fire = true;
    }
}

bool Spec::getBreak() const
{
    return (this->unbreak);
}

int Spec::getHealth() const
{
    return (this->_health);
}

int Spec::getId() const
{
    return (this->_id);
}

std::string Spec::getUid() const
{
    return (this->_uid);
}

void Spec::setUid(std::string uid)
{
    this->_uid = uid;
}

void Spec::giveDamage(int damage)
{
    this->_health -= damage;
    if (this->_health <= 0)
        this->_dead = true;
}

sf::Vector2f Spec::getSize() const
{
    return (this->_size);
}

int Spec::getDamage() const
{
    return (this->_damage);
}

bool Spec::getIsEnemy() const
{
    return (this->_enemy);
}

bool Spec::getIsDead() const
{
    return (this->_dead);
}



