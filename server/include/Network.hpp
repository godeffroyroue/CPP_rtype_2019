/*
** EPITECH PROJECT, 2019
** server
** File description:
** Network
*/

#pragma once

#include "INetwork.hpp"
#include "UDPServer.hpp"

class Network : public INetwork {
	public:
		Network();
		~Network();
        void start();
        UDPServer *getServer();
		std::string _ip;
		unsigned short _port;
	private:
        UDPServer *_server;
};