/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLPhysic
*/

#include "SFMLPhysic.hpp"

SFMLPhysic::SFMLPhysic(sf::Vector2f move, sf::Vector2f pos)
{
    this->_move = move;
    this->_pos = pos;
}

SFMLPhysic::SFMLPhysic(std::shared_ptr<SFMLPhysic> &p2)
{
    this->_move = p2->_move;
    this->_pos = p2->_pos;
    this->_size = p2->_size;
}

SFMLPhysic::~SFMLPhysic()
{
}

bool SFMLPhysic::colision(sf::Vector2f pos, sf::Vector2f size)
{
    if ((this->_pos.x >= pos.x && this->_pos.x <= pos.x + size.x) || (this->_pos.x + this->_size.x >= pos.x && this->_pos.x + this->_size.x <= pos.x + size.x)){
        if ((this->_pos.y >= pos.y && this->_pos.y <= pos.y + size.y) || (this->_pos.y + this->_size.y >= pos.y && this->_pos.y + this->_size.y <= pos.y + size.y)){
            return (true);
        }
    }
    return (false);
}

void SFMLPhysic::setSize(float x, float y)
{
    this->_size.x = x;
    this->_size.y = y;
}

void SFMLPhysic::makeMove(float elapsed, int width, int lenght, bool enemy, int id)
{
    if (this->_pos.x > 0 && this->_pos.x + this->_size.x < width && !enemy && id != -1)
        this->_pos.x += this->_move.x * elapsed;
    if (enemy)
        this->_pos.x += this->_move.x * elapsed;
    if (this->_pos.y > 0 && this->_pos.y + this->_size.y < lenght){
        this->_pos.y += this->_move.y * elapsed;
    }
    if (id == -1){
        this->_pos.x += this->_move.x * elapsed;
    }
}

sf::Vector2f SFMLPhysic::getPos() const
{
    return (this->_pos);
}

sf::Vector2f SFMLPhysic::getMove() const
{
    return (this->_move);
}


void SFMLPhysic::setPos(float x, float y)
{
    this->_pos.x = x;
    this->_pos.y = y;
}
