/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ParseRequest
*/

#ifndef PARSEREQUEST_HPP_
#define PARSEREQUEST_HPP_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "Server.hpp"
#include "SFML/Network.hpp"
#include "Packet.hpp"
#include "Player.hpp"

class ParseRequest {
	public:
		ParseRequest(sf::Packet packet, unsigned short port, unsigned short hostport, sf::IpAddress ip);
		~ParseRequest();
		void nickname();
		void join_room();
		void create_room();
		void leave_room();
		void quit();
		void input();
		void death();
		void refresh();
		void start_game();
		void execute_command();
		const sf::Packet getPacket();
		Header get_Header(sf::Packet);
		unsigned short get_newPort();
		bool get_newRoom();
    private:
        int _id;
		unsigned short _port;
		unsigned short _hostport;
		bool newRoom;
		unsigned short _roomPort;
        sf::Packet _packet;
		void init_commands();
		sf::IpAddress _ip;
		typedef void(ParseRequest::*command)();
		command cmd;
		std::map<TypeRequest, command> _commands; 
};

#endif /* !PARSEREQUEST_HPP_ */
