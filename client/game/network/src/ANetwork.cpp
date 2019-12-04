/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ANetwork
*/

#include "ANetwork.hpp"

ANetwork::ANetwork(std::string ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
}

ANetwork::~ANetwork()
{
}

std::string ANetwork::getIp() const
{
    return (this->ip);
}

int ANetwork::getPort() const
{
    return (this->port);
}
