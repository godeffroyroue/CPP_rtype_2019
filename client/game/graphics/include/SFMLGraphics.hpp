/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLGraphics
*/

#ifndef SFMLGRAPHICS_HPP_
#define SFMLGRAPHICS_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include "IGraphics.hpp"

class SFMLGraphics : public IGraphics
{
	public:
		SFMLGraphics(sf::Texture texture, sf::Sprite sprite, int offset);
                SFMLGraphics(std::shared_ptr<SFMLGraphics> &p2);
                ~SFMLGraphics();
                void setPosition(float x, float y);
                std::vector<float> getPosition() const;
                void display(sf::RenderWindow& window);
                void setRect(sf::Vector2f size);
	private:
                sf::Texture texture;
                sf::Sprite sprite;
                sf::IntRect _rect;
                int _offset;
                int current;

};

#endif /* !SFMLGRAPHICS_HPP_ */
