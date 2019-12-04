/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UDPGame
*/

#ifndef UDPGAME_HPP_
#define UDPGAME_HPP_

#include <iostream>
#include <string>
#include <map>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "IUDPServer.hpp"
#include "Player.hpp"
#include "EntityLoader.hpp"

class UDPGame : IUDPServer {
    public:
        UDPGame(unsigned short port, std::string nameRoom);
        ~UDPGame();
		std::map<unsigned short, Player *> _players;
		void run();
		std::map<unsigned short, Player *> getPlayers() {return (_players);};
        Player *getPlayer(unsigned short port) {return (_players.find(port)->second);};
        void addPlayers(unsigned short port, std::string username, sf::IpAddress ip);
        void removePlayers(unsigned short port);
        unsigned short getPlayerbyUUID(std::string uuid) {
            for (auto at : _players) {
                if (at.second->getUUID() == uuid)
                    return (at.first);
            }
            return (0);
        };
        int getNbrPlayers();
        int generateID();
        std::string getNameRoom();
        void broadcast(sf::Packet packet);
		unsigned short get_value_from_map(std::map<unsigned short, UDPGame*> map, std::string str);
	private:
        std::string _nameRoom;
        IEntity *generator_BOSS();
        void loadEntity();
        bool verifConnection();
        void manageClock();
        void waitingPlayers();
        void manageMonster(bool boolen);
        std::shared_ptr<EntityLoader> _load;
        std::vector<IEntity *> _all;
        std::vector<IEntity *> _commons;
        std::vector<IEntity *> _current;
        int _wave;
		unsigned short _port;
        size_t _maxPlayers;
        int _nbrMonster;
        bool _isRun;
        sf::Clock _clock;
        sf::Time _elapsed;
        sf::Clock _clockGame;
        sf::Time _elapsedGame;
		sf::UdpSocket server_socket;
        float _generation_interval;
};

#endif /* !UDPGAME_HPP_ */
