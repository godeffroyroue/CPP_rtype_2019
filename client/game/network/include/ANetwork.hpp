/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ANetwork
*/

#ifndef ANETWORK_HPP_
#define ANETWORK_HPP_

#include "INetwork.hpp"

class ANetwork {
	public:
		ANetwork(std::string ip, unsigned short port);
		~ANetwork();
                virtual bool send(std::string cmd) = 0;
                std::string getIp() const;
                int getPort() const;
	private:
                std::string ip;
                unsigned short port;
};

#endif /* !ANETWORK_HPP_ */
