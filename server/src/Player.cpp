/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::string username, unsigned short port, sf::IpAddress ip)
{
    _ip = ip;
    _username = username;
    _port = port;
    _id = 0;
    _connected = false;
    _x, _y = 0;
    _uuid = boost::uuids::random_generator()();
}

Player::~Player()
{
}

bool Player::getConnect()
{
    return (_connected);
}

std::string Player::getUsername()
{
    return (_username);
}

unsigned short Player::getPort()
{
    return (_port);
}

void Player::setID(int id)
{
    _id = id;
}

void Player::setX(int x)
{
    _x = x;
}

void Player::setY(int y)
{
    _y = y;
}

std::string Player::getUUID()
{
    return (boost::lexical_cast<std::string>(_uuid));
}

int Player::getID()
{
    return (_id);
}
