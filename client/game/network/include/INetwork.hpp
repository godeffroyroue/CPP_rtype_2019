/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include <iostream>
#include <vector>

class INetwork {
	public:
		virtual ~INetwork(){};
                virtual bool send(std::string cmd) = 0;
                virtual std::string getIp() const = 0;
                virtual int getPort() const = 0;
	private:
        std::string ip;
        unsigned short port;
};

#endif /* !INETWORK_HPP_ */
