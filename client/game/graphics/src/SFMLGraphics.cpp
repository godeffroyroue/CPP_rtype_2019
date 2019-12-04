/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLGraphics
*/

#include "SFMLGraphics.hpp"

SFMLGraphics::SFMLGraphics(sf::Texture texture, sf::Sprite sprite, int offset)
{
    this->sprite = sprite;
    this->texture = texture;
    this->_offset = offset;
    this->current = 0;
    this->sprite.setTexture(this->texture);
}

SFMLGraphics::SFMLGraphics(std::shared_ptr<SFMLGraphics> &p2)
{
    this->sprite = p2->sprite;
    this->texture = p2->texture;
    this->_offset = p2->_offset;
    this->current = 0;
    this->_rect = p2->_rect;
}


SFMLGraphics::~SFMLGraphics()
{
}

void SFMLGraphics::setRect(sf::Vector2f size)
{
    this->_rect.height = size.y;
    this->_rect.width = size.x;
    this->_rect.top = 0;
    this->_rect.left = 0;
}

void SFMLGraphics::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

void SFMLGraphics::display(sf::RenderWindow& window)
{
    if (this->current == this->_offset){
        this->current = 0;
        this->_rect.left = 0;
    }
    this->sprite.setTextureRect(this->_rect);
    window.draw(this->sprite);
    if (this->_offset)
        this->current++;
    this->_rect.left += this->_rect.width;
}

std::vector<float> SFMLGraphics::getPosition() const
{
    std::vector<float> pos;
    sf::Vector2f spos = this->sprite.getPosition();

    pos.push_back(spos.x);
    pos.push_back(spos.y);
    return (pos);
}
