/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UDPGame
*/

#include "UDPGame.hpp"
#include "ParseRequest.hpp"

UDPGame::UDPGame(unsigned short port, std::string nameRoom)
{
    _port = port;
    _nameRoom = nameRoom;
    _maxPlayers = 2;
	_wave = 0;
	_isRun = false;
	_generation_interval = 17;
	_nbrMonster = 3;
	std::cout << GRN << "[+]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " is currently created." << RESET << std::endl;
}

UDPGame::~UDPGame()
{
	std::cout << RED << "[-]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " is currently shutdown ..." << RESET << std::endl;
}

unsigned short UDPGame::get_value_from_map(std::map<unsigned short, UDPGame *> map, std::string str)
{
	for (auto it = map.begin(); it != map.end(); ++it) {
    	if (it->second->getNameRoom() == str)
        	return (it->first);
	}
	return (0);
}

int UDPGame::generateID()
{
	bool found = true;
	for (int i = 1; i != (int)_maxPlayers + 1; i++) {
		for (auto it : _players) {
			if (it.second->getID() == i)
				found = false;
		}
		if (found == true)
			return (i);
		found = true;
	}
	return (0);
}

void UDPGame::addPlayers(unsigned short port, std::string username, sf::IpAddress ip)
{
	Player *player = new Player(username, port, ip);
	int newid = generateID();
	player->setID(newid);
	player->setX(50);
	player->setY(50 * newid);
    _players[port] = player;
    std::cout << YEL << "[INFO]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " got 1 more player named (" << player->getPort() << "),(" << player->getUsername() << "), uuid:(" << player->getUUID() << ").[" << getNbrPlayers() << "/" << _maxPlayers << "]" << RESET << std::endl;
}

void UDPGame::removePlayers(unsigned short port)
{
    _players.erase(port);
    std::cout << YEL << "[INFO]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " got 1 player less named (" << port << "),(" << _players.find(port)->second << ")[" << getNbrPlayers() << "/" << _maxPlayers << "]" << RESET << std::endl;
}

int UDPGame::getNbrPlayers()
{
    return (_players.size());
}

std::string UDPGame::getNameRoom()
{
    return (_nameRoom);
}

void UDPGame::broadcast(sf::Packet packet)
{
	for (auto at : _players) {
		server_socket.send(packet, at.second->getIP(), at.second->getPort());
	}
	packet.clear();
}

bool UDPGame::verifConnection()
{
	for (auto at : _players) {
		if (at.second->getConnect() == false)
			return (false);
	}
	return (true);
}

void UDPGame::waitingPlayers()
{
	sf::Packet packet;
    sf::IpAddress sender;
	unsigned short senderPort;
	server_socket.setBlocking(false);

	while (_isRun != true) {
		if ((size_t)getNbrPlayers() == _maxPlayers && verifConnection()) {
			sf::Packet packet;
			Header res_header;
			res_header.cmd = START_GAME;
			res_header.length = (int)_maxPlayers;
			res_header.magic_code = 356;
			packet << res_header;
			for (auto at : _players)
				packet << at.second->getID() << at.second->getUUID() << at.second->getX() << at.second->getY();
			broadcast(packet);
			packet.clear();
			_isRun = true;
			break;
		}
		if (server_socket.receive(packet, sender, senderPort) == sf::Socket::Done) {
			ParseRequest *request = new ParseRequest(packet, senderPort, _port, sender);
			sf::Packet res = request->getPacket();
			(res.getDataSize() != 0) ? server_socket.send(res, sender, senderPort) : 0;
		}
	}
}

IEntity *UDPGame::generator_BOSS()
{
	for (auto at : _all) {
		if (at->getHealth() >= 500)
			return (at);
	}
	return (NULL);
}

void UDPGame::manageMonster(bool boolen)
{
	sf::Packet p;

	if (boolen) {
		Header header;
		header.length = 1;
		header.magic_code = 356;
		header.cmd = INPUT;
		IEntity *monster = generator_BOSS();
		boost::uuids::uuid uuid = boost::uuids::random_generator()();
		std::cout << YEL << "[GENERATOR]" << RED << "[BOSS]" << WHT << ":[" << monster->getId() << "]" << "(" << boost::lexical_cast<std::string>(uuid) << ")" << "x[" << 1620 << "], y[" << 880/2 << "]." << RESET << std::endl;
		p << header << monster->getId() << boost::lexical_cast<std::string>(uuid) << (float)1620 << (float)880/3;
		broadcast(p);
	}
	else {
		Header header;
		header.magic_code = 356;
		header.cmd = INPUT;
		header.length = _nbrMonster;
		p << header;
		for (int i = 1; i != _nbrMonster + 1; i++) {
			int id = std::rand() % (7 + 1 - 5) + 5;
			boost::uuids::uuid uuid = boost::uuids::random_generator()();
			std::cout << YEL << "[GENERATOR]" << RED << "[COMMON]" << WHT << ":[" << id << "]" << "(" << boost::lexical_cast<std::string>(uuid) << ")" << "x[" << 1620 << "], y[" << 200*i << "]." << RESET << std::endl;
			p << id << boost::lexical_cast<std::string>(uuid) << (float)(1620) << (float)(200 * i);
		}
		broadcast(p);
	}
	p.clear();
}

void UDPGame::manageClock()
{
	_elapsed += _clock.restart();
	_elapsedGame += _clockGame.restart();
	if (_elapsed.asSeconds() >= _generation_interval) {
		_elapsed = _clock.restart();
		if (_wave == 3) {
			_wave = 0;
			manageMonster(true);
		}
		else {
			_wave++;
			manageMonster(false);
		}
	}
	if (_elapsedGame.asSeconds() >= 60) {
		_elapsedGame = _clockGame.restart();
		if (_generation_interval >= 4) {
			_generation_interval--;
		}
	}
}

void UDPGame::loadEntity()
{
    _load = std::shared_ptr<EntityLoader>(new EntityLoader());
    _load->getEntityVector();
    std::vector<void *> hdl = _load->getHandleList();
    std::vector<IEntity*> tmp;
    std::cout << hdl.size() << std::endl;
	for (auto it : hdl) {
		if (_load->getInstanceWithHandle(it)->getId() >= 5 && _load->getInstanceWithHandle(it)->getId() <= 8) {
			_all.push_back(_load->getInstanceWithHandle(it));
			if (_load->getInstanceWithHandle(it)->getHealth() < 500) {
				_commons.push_back(_load->getInstanceWithHandle(it));
			}
		}
	}
}

void UDPGame::run()
{
	server_socket.bind(_port);
	std::cout << YEL << "[INFO]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " is currently loading all packages..." << RESET << std::endl;
	loadEntity();
	std::cout << YEL << "[INFO]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " finished to load all packages..." << RESET << std::endl;
	std::cout << YEL << "[INFO]" << WHT << "ROOM[" << _port << "] as name:" << _nameRoom << " is currently running. ... [0/" << _maxPlayers << "] players." << RESET << std::endl;
	sf::Packet packet;
    sf::IpAddress sender;
	unsigned short senderPort;
	server_socket.setBlocking(false);
	waitingPlayers();
	_elapsed = _clock.restart();
	_elapsedGame = _clockGame.restart();
	while (_isRun) {
		manageClock();
		if (server_socket.receive(packet, sender, senderPort) == sf::Socket::Done) {
			ParseRequest *request = new ParseRequest(packet, senderPort, _port, sender);
			sf::Packet res = request->getPacket();
			(res) ? server_socket.send(res, sender, senderPort) : 0;
		}
	}
}