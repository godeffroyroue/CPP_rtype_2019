/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <iostream>
#include "SFML/Network.hpp"
#include "EntityLoader.hpp"

enum TypeRequest {
	NICKNAME = 0, 
	JOIN_ROOM = 1,
	CREATE_ROOM = 2,
	LEAVE_ROOM = 3,
	QUIT = 4,
	INPUT = 5,
	DEATH = 6,
	REFRESH = 7,
	START_GAME = 8
};

enum Keyboard : int {
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	SPACEBAR = 4
};

enum response {
	ERROR = 0,
	OK = 1
};

struct Header {
	int magic_code;
	int cmd;
	int length;
};

inline sf::Packet& operator <<(sf::Packet& packet, std::map<unsigned short, std::string> &map)
{
	for (auto it = map.begin(); it != map.end(); it++)
		packet << it->second;
	return (packet);
}

inline sf::Packet& operator >>(sf::Packet& packet, response& response)
{
	return packet >> response;
}

inline sf::Packet& operator <<(sf::Packet& packet, const Header& header)
{
	return packet << header.magic_code << header.cmd << header.length;
}

inline sf::Packet& operator >>(sf::Packet& packet, Header& header)
{
	return packet >> header.magic_code >> header.cmd >> header.length;
}

inline sf::Packet& operator >>(sf::Packet& packet, Keyboard& keyboard)
{
	return packet >> keyboard;
}

inline sf::Packet& operator <<(sf::Packet& packet, Keyboard& keyboard)
{
	return packet << keyboard;
}

template<class T>
sf::Packet& operator >>(sf::Packet& Packet, std::vector<T>& A)
{
	Header header;
	Packet >> header;
	A.reserve(header.length);
	for (int i = 0;i < header.length; i++) {
		T temp;
		Packet >> temp;
		A.push_back(temp);
	}
	return Packet;
}

template<class T>
sf::Packet& operator <<(sf::Packet& Packet, const std::vector<T>& A)
{
	for (size_t i = 0;i < A.size(); i++) {
		Packet << A[i];
	}
	return Packet;
}

#endif /* !PACKET_HPP_ */
