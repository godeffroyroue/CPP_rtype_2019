/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLMenu
*/

#ifndef SFMLMENU_HPP_
#define SFMLMENU_HPP_

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include "IMenu.hpp"
#include "Packet.hpp"

#define WIDTH 1200
#define HEIGHT 800
#define FRAME_LIMIT 30
#define MAGIC 356


typedef struct graphic_s
{
        sf::Texture texture;
        sf::Sprite sprite;
}   graphic_t;

typedef struct button_s
{
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Color color;
    sf::Text text;
    std::string name;
    sf::RectangleShape rectangle;
    bool active;
}   button_t;

typedef struct room_s
{
    sf::Text text;
    std::string name;
    bool selected;
}   room_t;

class SFMLMenu : public IMenu
{
	public:
		SFMLMenu();
		~SFMLMenu();
                void run();
                void destroy();
                bool initMenu(sf::IpAddress serverIp, unsigned short port);
                void eventHandling(sf::Event event);
                bool getStart() const;
                bool getQuit() const;
                button_t addButton(sf::Vector2f size, sf::Vector2f pos, std::string name, sf::Color color, bool active);
                void drawButton();
                void getRoomAvailable();
                void drawRooms();
                void requestRoom();
                std::string getIp() const;
                void joinRoom();
                std::string getUid() const;
                int getId() const;
                unsigned short getSockPort() const;
                unsigned short getPort() const;
                void cmdHandling(Header header);
                bool isRoom(std::string name);
                void addRoom(std::string name);
	private:
                std::string username;
                bool start = false;
                bool quit = false;
                sf::RenderWindow window;
                graphic_t background;
                sf::Font font;
                button_t input;
                std::vector<button_t> button;
                std::vector<room_t> rooms;
                std::string selectedRoom;
                std::string player_input;
                sf::UdpSocket socket;
                sf::IpAddress serverIp;
                sf::Packet packet;
                unsigned short port;
                int id;
                std::string uid;
                unsigned short sport;

};

#endif /* !SFMLMENU_HPP_ */
