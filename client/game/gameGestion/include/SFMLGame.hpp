/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLGame
*/

#ifndef SFMLGAME_HPP_
#define SFMLGAME_HPP_

#include <memory>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <SFML/System.hpp>
#include "IGame.hpp"
#include "entityManager.hpp"
#include "SFMLNetwork.hpp"

#define IPSERVER "127.0.0.1"
#define W 1620
#define H 880
#define FPS 30
#define MOVING 5

typedef struct paralax_s
{
        int speed;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f pos;
        sf::Vector2f size;
}       paralax_t;

class SFMLGame : public IGame
{
	public:
		SFMLGame();
		~SFMLGame();
                bool initGame(unsigned short port, int id, std::string uid, unsigned short sport, std::string serverIp);
                void startGame();
                void display();
                std::shared_ptr<Entity> getPlayer();
                void makeMove(float elapsed);
                void checkUnbreak();
                bool checkDeath();
                void eventHandling(sf::Event event);
                void keyManagement(sf::Event event);
                void displayInfo(std::shared_ptr<Entity> player);
                void enemyShoot();
                void startUpdate();
                bool initParalax();
                bool addParalax(sf::Vector2f size, sf::Vector2f pos, int speed, std::string path);
                void displayParalax();
                void destroy();
	private:
                int level;
                int xp;
                int playerId;
                bool isDone;
                int id;
                std::string uid;
                std::shared_ptr<EntityManager> manager;
                std::shared_ptr<SFMLNetwork> network;
                std::vector<std::shared_ptr<paralax_t>> plx;
                sf::RenderWindow window;
                sf::Font font;
};

#endif /* !SFMLGAME_HPP_ */