/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Network
*/

#include "Network.hpp"

Network::Network()
{
}

Network::~Network()
{
}

void Network::start()
{
    try {
        _server = new UDPServer(_port, _ip);
        _server->run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

UDPServer *Network::getServer()
{
    return (_server);
}