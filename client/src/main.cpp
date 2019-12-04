/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** main
*/

#include "r-type_client.hpp"
#include <memory>
#include "SFMLMenu.hpp"
#include "SFMLGame.hpp"

void printUsage()
{
    std::cout << "USAGE\n\t./build/bin/r-type_client ip port\n" << std::endl;
    std::cout << "DESCRIPTION\n\tip\tip of the server\n\tport\tport of the server" << std::endl;
    exit(84);
}

int main(int argc, char **argv)
{
    std::shared_ptr<SFMLMenu> menu = std::shared_ptr<SFMLMenu>(new SFMLMenu());
    std::shared_ptr<IGame> game = std::shared_ptr<SFMLGame>(new SFMLGame());
    sf::IpAddress serverIp;
    unsigned short port;

    if (argc != 3)
        printUsage();
    try{
        serverIp = argv[1];
        port = (unsigned short) strtoul(argv[2], NULL, 0);
    }
    catch(std::exception const &e){
        printUsage();
    }
    while (!menu->getQuit()){
        if (!menu->initMenu(serverIp, port))
            return (84);
        menu->run();
        if (menu->getStart()){
            if (game->initGame(menu->getPort(), menu->getId(), menu->getUid(), menu->getSockPort(), menu->getIp()))
                return (84);
            std::cout << "start game" << std::endl;
            game->startGame();
            game->destroy();
        }
        menu->destroy();
    }
}