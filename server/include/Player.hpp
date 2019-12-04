/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player {
	public:
		Player(std::string username, unsigned short port, sf::IpAddress ip);
        Player(const Player *player) {
            _ip = player->_ip;
            _id = player->_id;
            _x = player->_x;
            _y = player->_y;
            _uuid = player->_uuid;
            _port = player->_port;
            _username = player->_username;
            _connected = player->_connected;
        } 
		~Player();
        std::string getUsername();
        unsigned short getPort();
        std::string getUUID();
        int getID();
        int getX() {return (_x);};
        int getY() {return (_y);};
        sf::IpAddress getIP() {return(_ip);};
        void setX(int x);
        void setY(int y);
        void setID(int id);
        bool getConnect();
        void setPort(unsigned short port) {
            _port = port;
        };
        void setConnect(bool state) {
            std::cout << "[" << _port << "] is now (Connected)" << std::endl;
            _connected = state;
        };
        sf::IpAddress _ip;
        int _id;
        int _x;
        int _y;
        boost::uuids::uuid _uuid;
        unsigned short _port;
        std::string _username;
        bool _connected;
	private:
};

#endif /* !PLAYER_HPP_ */
