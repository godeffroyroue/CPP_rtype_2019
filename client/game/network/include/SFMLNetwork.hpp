/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLNetwork
*/

#ifndef SFMLNETWORK_HPP_
#define SFMLNETWORK_HPP_

#include <SFML/Network.hpp>
#include <memory>
#include "ANetwork.hpp"
#include "Packet.hpp"
#include "entityManager.hpp"

#define MAGIC 356

class SFMLNetwork
{
	public:
		SFMLNetwork(std::string ip, unsigned short port, unsigned short sport);
		~SFMLNetwork();
		void sendStart(std::string uuid);
        bool send(sf::Packet packet);
		bool getStart(std::shared_ptr<EntityManager> manager);
		void sendPos(int id, std::string uuid, float x, float y);
		void update(std::shared_ptr<EntityManager> manager, int id_client, std::string uuid_client);
		void sendDeath(int id, std::string uuid);
	private:
		sf::IpAddress serverIp;
        sf::Packet packet;
        sf::UdpSocket socket;
		unsigned short port;

};

#endif /* !SFMLNETWORK_HPP_ */
