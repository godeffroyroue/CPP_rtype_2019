/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLMenu
*/

#include "SFMLMenu.hpp"

SFMLMenu::SFMLMenu()
{

}

SFMLMenu::~SFMLMenu()
{

}

std::string SFMLMenu::getIp() const
{
    return (this->serverIp.toString());
}

int SFMLMenu::getId() const
{
    return (this->id);
}

std::string SFMLMenu::getUid() const
{
    return (this->uid);
}

unsigned short SFMLMenu::getPort() const
{
    return (this->port);
}

void SFMLMenu::destroy()
{
    std::cout << "destroy" << std::endl;
    this->button.clear();
    this->rooms.clear();
}

bool SFMLMenu::getQuit() const
{
    return (this->quit);
}

bool SFMLMenu::getStart() const
{
    return (this->start);
}

void SFMLMenu::requestRoom()
{
    sf::Packet p;
    Header header;
    header.cmd = TypeRequest::CREATE_ROOM;
    header.magic_code = MAGIC;
    header.length = 1;
    if (this->player_input.size() != 0){
        p << header << this->player_input;
        this->socket.send(p, this->serverIp, this->port);
    }
}

button_t SFMLMenu::addButton(sf::Vector2f size, sf::Vector2f pos, std::string name, sf::Color color, bool active)
{
    button_t btn;
    float posx = pos.x - (11 * name.size() / 2);
    float posy = pos.y - (size.y / 2.5);

    btn.size.x = size.x;
    btn.size.y = size.y;
    btn.pos.x = pos.x;
    btn.pos.y = pos.y;
    btn.color = color;
    btn.text.setString(name);
    btn.text.setCharacterSize(20);
    btn.text.setPosition(posx, posy);
    btn.active = active;
    btn.text.setFillColor(sf::Color::Black);
    btn.rectangle.setSize(btn.size);
    btn.rectangle.setPosition(btn.pos);
    btn.rectangle.setFillColor(btn.color);
    btn.rectangle.setOrigin(size.x/2, size.y/2);
    btn.name = name;
    btn.text.setFont(this->font);
    return (btn);
}

void SFMLMenu::drawButton()
{
    for (button_t b : this->button){
        if (b.active){
            this->window.draw(b.rectangle);
            this->window.draw(b.text);
        }
    }
    this->window.draw(this->input.rectangle);
    this->window.draw(this->input.text);
}

bool SFMLMenu::initMenu(sf::IpAddress serverIp, unsigned short port)
{
    this->window.create(sf::VideoMode(WIDTH, HEIGHT), "R-Type Menu");
    if (!this->background.texture.loadFromFile("client/ressources/menu.png"))
        return (false);
    if (!this->font.loadFromFile("client/ressources/Lato-Black.ttf"))
        return (false);
    this->background.sprite.setTexture(this->background.texture);
    this->window.setFramerateLimit(FRAME_LIMIT);
    this->button.push_back(addButton(sf::Vector2f(120, 35), sf::Vector2f(WIDTH/2, HEIGHT/2 + HEIGHT/3), "Quit", sf::Color (133, 116, 73), true));
    this->button.push_back(addButton(sf::Vector2f(120, 35), sf::Vector2f(WIDTH/10, HEIGHT/2 + HEIGHT/3), "Refresh", sf::Color (133, 116, 73), true));
    this->button.push_back(addButton(sf::Vector2f(120, 35), sf::Vector2f(WIDTH/2, HEIGHT/2 + HEIGHT/5), "Start", sf::Color (133, 116, 73), true));
    this->button.push_back(addButton(sf::Vector2f(120, 35), sf::Vector2f(WIDTH/3 + WIDTH/5, HEIGHT/5 + HEIGHT/6.6), "Create", sf::Color (133, 116, 73), true));
    this->input = addButton(sf::Vector2f(150, 30), sf::Vector2f(WIDTH/4 + WIDTH/10, HEIGHT/3), "", sf::Color (133, 116, 73), false);
    this->input.rectangle.setOrigin(0, 0);
    this->input.text.setPosition(this->input.rectangle.getPosition().x, this->input.rectangle.getPosition().y);
    this->selectedRoom = "";
    this->player_input = "";
    this->serverIp = serverIp;
    this->start = false;
    this->quit = false;
    this->port = port;
    this->socket.bind(0, this->serverIp);
    this->sport = this->socket.getLocalPort();
    return(true);
}

bool isInButton(sf::Vector2i position, button_t button)
{
    sf::Vector2f pos = button.rectangle.getPosition();    
    float posx = pos.x - button.size.x / 2;
    float posy = pos.y - button.size.y / 2;

    if (position.x >= posx && position.x <= posx + button.size.x && position.y >= posy && position.y <= posy + button.size.y){
        return (true);
    }
    return (false);
}

unsigned short SFMLMenu::getSockPort() const
{
    return(this->sport);
}

bool SFMLMenu::isRoom(std::string name)
{
    bool exist = false;
    room_t new_room;

    for (room_t r : this->rooms){
        if (r.name == name)
            exist = true;
    }
    return (exist);
}

void SFMLMenu::getRoomAvailable()
{
    sf::Packet p;
    Header header;

    header.cmd = TypeRequest::REFRESH;
    header.magic_code = MAGIC;
    header.length = 0;
    p << header;
    this->socket.send(p, this->serverIp, this->port);
}

void SFMLMenu::drawRooms()
{
    int posx = 70;
    int posy = 250;

    for (size_t i = 0; i < this->rooms.size(); i++){
        this->rooms[i].text.setPosition(posx, posy);
        this->window.draw(this->rooms[i].text);
        posy += 20;
    }
}

bool isInRoom(sf::Vector2i position, room_t room)
{
    sf::Vector2f pos = room.text.getPosition();

    if (position.x >= pos.x && position.x <= pos.x + 10 * room.name.size() && position.y >= pos.y && position.y <= pos.y + 20){
        return (true);
    }
    return (false);
}

bool isAlphaNum(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (true);
    if (c >= 'a' && c <= 'z')
        return (true);
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

void SFMLMenu::joinRoom()
{
    sf::Packet p;
    Header header;

    header.cmd = TypeRequest::JOIN_ROOM;
    header.magic_code = MAGIC;
    header.length = 1;
    p << header << this->selectedRoom;
    this->socket.send(p, this->serverIp, this->port);
    this->sport = this->socket.getLocalPort();
}

void SFMLMenu::eventHandling(sf::Event event)
{
    while (window.pollEvent(event)){
        sf::Vector2i position = sf::Mouse::getPosition(this->window);
        for (size_t i = 0; i < this->button.size(); i++){
            if (isInButton(position, button[i]))
                button[i].rectangle.setFillColor(sf::Color::Green);
            else
                button[i].rectangle.setFillColor(sf::Color (133, 116, 73));
        }
        if (this->input.active)
            this->input.rectangle.setFillColor(sf::Color::White);
        else
            this->input.rectangle.setFillColor(sf::Color (133, 116, 73));
        for (size_t i = 0; i < this->rooms.size(); i++){
            if (isInRoom(position, this->rooms[i]) && !this->rooms[i].selected)
                this->rooms[i].text.setFillColor(sf::Color::Green);
            else if(this->rooms[i].selected)
                this->rooms[i].text.setFillColor(sf::Color::Red);
            else
                this->rooms[i].text.setFillColor(sf::Color::White);
        }
        if (event.type == sf::Event::TextEntered && this->input.active && isAlphaNum(event.text.unicode) && this->player_input.size() < 14){
            this->player_input += event.text.unicode;
            this->input.text.setString(player_input);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->player_input.size() > 0){
            this->player_input = this->player_input.substr(0, this->player_input.size() - 1);
            this->input.text.setString(player_input);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            for (size_t i = 0; i < this->button.size(); i++){
                if (isInButton(position, button[i]) && button[i].active && button[i].name == "Quit"){
                    this->quit = true;
                    window.close();
                }
                if (isInButton(position, button[i]) && button[i].active && button[i].name == "Refresh"){
                    getRoomAvailable();
                }
                if (isInButton(position, button[i]) && button[i].active && button[i].name == "Create" && !isRoom(this->player_input)){
                    requestRoom();
                    this->player_input.clear();
                    this->input.text.setString(player_input);
                }
                if (isInButton(position, button[i]) && button[i].active && button[i].name == "Start" && this->selectedRoom.size() != 0){
                    joinRoom();
                    button[i].active = false;
                }
            }
            if (position.x >= this->input.pos.x && position.x <= this->input.pos.x + this->input.size.x && position.y >= this->input.pos.y && position.y <= this->input.pos.y + this->input.size.y)
                this->input.active = true;
            else
                this->input.active = false;
            for (size_t i = 0; i < this->rooms.size(); i++){
                if (isInRoom(position, this->rooms[i])) {
                    for (size_t i = 0; i < this->rooms.size(); i++){
                        if (this->rooms[i].selected)
                            this->rooms[i].selected = false;
                    }
                    this->rooms[i].selected = true;
                    this->selectedRoom = this->rooms[i].name;
                }
            }
        }
        if (event.type == sf::Event::Closed){
            this->quit = true;
            window.close();
        }
    }
}

void SFMLMenu::addRoom(std::string name)
{
    room_t newR;

    newR.text.setString(name);
    newR.text.setCharacterSize(20);
    newR.text.setFont(this->font);
    newR.name = name;
    newR.selected = false;
    this->rooms.push_back(newR);
}

void SFMLMenu::cmdHandling(Header header)
{
    if (header.magic_code != MAGIC)
        return;
    if (header.cmd == TypeRequest::CREATE_ROOM || header.cmd == TypeRequest::REFRESH){
        std::vector<std::string> data;
        this->packet >> data;
        this->rooms.clear();
        for (size_t i = 0; i < data.size(); i++)
            addRoom(data[i]);
    }
    if(header.cmd == TypeRequest::JOIN_ROOM){
        unsigned short new_port = 0;
        std::string uuid;
        int id;
        if (this->packet >> header >> new_port >> id >> uuid && new_port != response::ERROR){
            this->start = true;
            this->port = new_port;
            this->id = id;
            this->uid = uuid;
            this->window.close();
        }
    }
}

void SFMLMenu::run()
{
    this->socket.setBlocking(false);
    while (window.isOpen()) {
        sf::IpAddress server = this->serverIp;
        unsigned short sport = this->port;
        if (this->socket.receive(this->packet, server, sport) == sf::Socket::Done){
            sf::Packet p = this->packet;
            Header header;
            p >> header;
            cmdHandling(header);
        }
        sf::Event event;
        eventHandling(event);
        window.clear(sf::Color::White);
        window.draw(this->background.sprite);
        drawButton();
        drawRooms();
        window.display();
    }
    this->socket.unbind();
}
