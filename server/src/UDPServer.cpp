/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** UDPServer
*/

#include "UDPServer.hpp"
#include "ParseRequest.hpp"

UDPServer::UDPServer(unsigned short port, std::string ip) : _port(port), _ip(ip)
{
}

UDPServer::~UDPServer()
{
}

unsigned short UDPServer::get_value_from_map(std::map<unsigned short, UDPGame *> map, std::string str)
{
	for (auto it = map.begin(); it != map.end(); ++it) {
    	if (it->second->getNameRoom() == str)
        	return (it->first);
	}
	return (0);
}

unsigned short UDPServer::newRoom()
{
	unsigned short newPort = 0;
	
	for (int i = 1; true; i++) {
		auto it = _threads.find(_port + i);
		if (it == _threads.end()) {
			newPort = (_port + i);
			break;
		}
	}
	return (newPort);
}

void entryPoint(UDPGame *server_game)
{
	try {
		server_game->run();
	}
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void UDPServer::addUDPGame(unsigned short port, std::string roomName)
{
	_rooms[port] = new UDPGame(port, roomName);
}

std::vector<std::string> UDPServer::getRooms()
{
	std::vector<std::string> vector;
	for (auto it = _rooms.begin(); it != _rooms.end(); it++) {
		vector.push_back(it->second->getNameRoom());
	}
	return (vector);
}

void UDPServer::run()
{
	server_socket.bind(_port, _ip);
	std::cout << YEL << "[SERVER] LISTENING ON PORT [" << _port << "], waiting for a message... " << RESET << std::endl;
	sf::Packet packet;
    sf::IpAddress sender;
	unsigned short senderPort;
	server_socket.setBlocking(false);
	while (true) {
		if (server_socket.receive(packet, sender, senderPort) == sf::Socket::Done) {
			ParseRequest *request = new ParseRequest(packet, senderPort, _port, sender);
			sf::Packet res = request->getPacket();
			if (request->get_newRoom()) {
				auto *thread = new sf::Thread(&entryPoint, _rooms.find(request->get_newPort())->second);
				_threads[request->get_newPort()] = thread;
				thread->launch();
			}
			server_socket.send(res, sender, senderPort);
		}
	}
}