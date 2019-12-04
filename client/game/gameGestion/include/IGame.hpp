/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <iostream>

class IGame {
	public:
		virtual ~IGame(){};
                virtual bool initGame(unsigned short port, int id, std::string uid, unsigned short sport, std::string serverIp) = 0;
                virtual void startGame() = 0;
                virtual void destroy() = 0;
	private:
                int level;
                int xp;
                int playerId;
                bool isDone;
};

#endif /* !IGAME_HPP_ */
