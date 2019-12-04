/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLPhysic
*/

#ifndef SFMLPHYSIC_HPP_
#define SFMLPHYSIC_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

class SFMLPhysic {
	public:
		SFMLPhysic(sf::Vector2f move, sf::Vector2f pos);
                SFMLPhysic(std::shared_ptr<SFMLPhysic> &p2);
                ~SFMLPhysic();
                void makeMove(float elapsed, int width, int lenght, bool enemy, int id);
                sf::Vector2f getPos() const;
                sf::Vector2f getMove() const;
                void setPos(float x, float y);
                void setSize(float x, float y);
                bool colision(sf::Vector2f pos, sf::Vector2f size);
	private:
                sf::Vector2f _move;
                sf::Vector2f _pos;
                sf::Vector2f _size;

};

#endif /* !SFMLPHYSIC_HPP_ */
