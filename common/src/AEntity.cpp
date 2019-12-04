/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AEntity
*/

#include "AEntity.hpp"

AEntity::AEntity(int health, int id, int damage, bool enemy, std::vector<float> size, std::vector<float> pos, std::vector<float> move, std::string texture, int offset, int idShoot, int freqShoot)
{
    this->_health = health;
    this->_id = id;
    this->_damage = damage;
    this->_enemy = enemy;
    this->_size = size;
    this->_pos = pos;
    this->_move = move;
    this->_texture = texture;
    this->_offset = offset;
    this->_idShoot = idShoot;
    this->_freqShoot = freqShoot;
}

int AEntity::getId() const
{
    return (this->_id);
}

int AEntity::getHealth() const
{
    return (this->_health);
}

std::string AEntity::getTexturePath() const
{
    return (this->_texture);
}

std::vector<float> AEntity::getSize() const
{
    return (this->_size);
}

std::vector<float> AEntity::getMove() const
{
    return (this->_move);
}

std::vector<float> AEntity::getPos() const
{
    return (this->_pos);
}

int AEntity::getOffset() const
{
    return (this->_offset);
}

bool AEntity::getEnemy() const
{
    return (this->_enemy);
}

int AEntity::getDamage() const
{
    return (this->_damage);
}

int AEntity::getIdShoot() const
{
    return (this->_idShoot);
}

int AEntity::getFreqShoot() const
{
    return (this->_freqShoot);
}

