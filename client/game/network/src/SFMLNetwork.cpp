/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLNetwork
*/

#include "SFMLNetwork.hpp"

SFMLNetwork::SFMLNetwork(std::string ip, unsigned short port, unsigned short sport)
{
    this->serverIp = ip;
    this->port = port;
    this->socket.bind(sport, ip);
}

SFMLNetwork::~SFMLNetwork()
{
}

void SFMLNetwork::sendStart(std::string uuid)
{
    sf::Packet p;
    Header hdr;

    hdr.cmd = START_GAME;
    hdr.magic_code = MAGIC;
    hdr.length = 0;
    p << hdr << uuid;
    this->send(p);
}

void SFMLNetwork::sendPos(int id, std::string uuid, float x, float y)
{
    sf::Packet p;
    Header hdr;

    hdr.cmd = INPUT;
    hdr.magic_code = MAGIC;
    hdr.length = 1;
    p << hdr << id << uuid << x << y;
    this->send(p);
}

bool SFMLNetwork::getStart(std::shared_ptr<EntityManager> manager)
{
	sf::IpAddress ips;
	unsigned short ports;
    sf::Packet p;
    Header hdr;
    int id = 0;
    std::string uuid;
    int x = 0;
    int y = 0;

    this->socket.setBlocking(false);
    while (1){
        if (this->socket.receive(p, ips, ports) == sf::Socket::Done){
            p >> hdr;
            for (int i = 0; i != hdr.length; i++) {
                p >> id >> uuid >> x >> y;
                manager->addEntity(id, uuid, sf::Vector2f(x, y));
            }
            return (true);
        }
    }
    return(false);
}


void SFMLNetwork::update(std::shared_ptr<EntityManager> manager, int id_client, std::string uuid_client)
{
    sf::IpAddress ips;
	unsigned short ports;
    sf::Packet p;
    Header hdr;
    int id = 0;
    std::string uuid;
    float x = 0;
    float y = 0;

    
    this->socket.setBlocking(true);
    while (1){
        if (this->socket.receive(p, ips, ports) == sf::Socket::Done){
            p >> hdr;
            for (int i = 0; i != hdr.length; i++) {
                if (p >> id >> uuid >> x >> y){
                    if (id != id_client && uuid != uuid_client){
                        bool exist = false;
                        for (std::shared_ptr<Entity> ent : manager->getCurrent()){
                            if (ent->getSpec()->getUid() == uuid && ent->getSpec()->getId() == id){
                                ent->getPhysic()->setPos(x, y);
                                ent->getGraph()->setPosition(x, y);
                                exist = true;
                                break;
                            }
                        }
                        if (!exist){
                            manager->addEntity(id, uuid, sf::Vector2f(x, y));
                        }
                    }
                }
            }
        }
    }
}

void SFMLNetwork::sendDeath(int id, std::string uuid)
{
    sf::Packet p;
    Header hdr;

    hdr.cmd = DEATH;
    hdr.magic_code = MAGIC;
    hdr.length = 1;
    p << hdr << id << uuid;
    this->send(p);
}


bool SFMLNetwork::send(sf::Packet packet)
{
    sf::IpAddress ip = this->serverIp;
    unsigned short port = this->port;
    this->socket.send(packet, ip, port);
    packet.clear();
    return (true);
}
