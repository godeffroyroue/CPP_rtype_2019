/*
** EPITECH PROJECT, 2019
** server
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <iostream>
#include <string>
#include <map>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "UDPGame.hpp"

class UDPServer : IUDPServer {
	public:
		UDPServer(unsigned short port, std::string ip);
        ~UDPServer();
		std::map<unsigned short, std::string> _players;
		std::map<unsigned short, UDPGame *> _rooms;
		std::map<unsigned short, sf::Thread *> _threads;
		void run();
		unsigned short newRoom();
		std::vector<std::string> getRooms();
		void addUDPGame(unsigned short port, std::string roomName);
		std::map<unsigned short, std::string> getPlayers() {return (_players);};
		unsigned short get_value_from_map(std::map<unsigned short, UDPGame *> map, std::string str);
	private:
		unsigned short _port;
		std::string _ip;
		sf::UdpSocket server_socket;
};

#endif /* !UDPSERVER_HPP_ */
