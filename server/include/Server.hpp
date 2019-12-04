/*
** EPITECH PROJECT, 2019
** server
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "boost/program_options.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Network.hpp"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

class Server {
        private:
		Server();
	public:
		~Server() {};
                Network *_network;
                static Server* getInstance() {
                        static Server* instance = new Server();
                        return (instance);
                }
                Network *getNetwork();
};

#endif /* !SERVER_HPP_ */
