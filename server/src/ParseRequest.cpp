/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ParseRequest
*/

#include "ParseRequest.hpp"

ParseRequest::ParseRequest(sf::Packet packet, unsigned short port, unsigned short hostport, sf::IpAddress ip)
{
	_ip = ip;
	_packet = packet;
	_port = port;
	_hostport = hostport;
	Header header_req = get_Header(packet);
	_id = header_req.cmd;
	newRoom = false;
	_roomPort = 0;
	init_commands();
	execute_command();
}

ParseRequest::~ParseRequest()
{
}

void ParseRequest::init_commands()
{
	_commands.insert(std::make_pair(NICKNAME, &ParseRequest::nickname));
	_commands.insert(std::make_pair(JOIN_ROOM, &ParseRequest::join_room));
	_commands.insert(std::make_pair(CREATE_ROOM, &ParseRequest::create_room));
	_commands.insert(std::make_pair(LEAVE_ROOM, &ParseRequest::leave_room));
	_commands.insert(std::make_pair(QUIT, &ParseRequest::quit));
	_commands.insert(std::make_pair(INPUT, &ParseRequest::input));
	_commands.insert(std::make_pair(DEATH, &ParseRequest::death));
	_commands.insert(std::make_pair(REFRESH, &ParseRequest::refresh));
	_commands.insert(std::make_pair(START_GAME, &ParseRequest::start_game));
}

void ParseRequest::execute_command()
{
	for (std::map<TypeRequest, command>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
		if ((*it).first == (TypeRequest)_id)
			(*this.*_commands[(TypeRequest)_id])();
	}
}

Header ParseRequest::get_Header(sf::Packet packet)
{
	Header header;
	packet >> header;
	// std::cout << "header.magic_code:" << header.magic_code << std::endl;
	// std::cout << "header.cmd:" << header.cmd << std::endl;
	// std::cout << "header.length:" << header.length << std::endl;
	return (header);
}

const sf::Packet ParseRequest::getPacket()
{
	return (_packet);
}

void ParseRequest::refresh()
{
	std::cout << GRN << "[PACKET]" << WHT << " from sender [" << _port << "] to [" << _hostport << "] " << RESET;
	std::cout << CYN << "[REQUEST]" << WHT << "(REFRESH)" << RESET << std::endl;
	Header res_header;
	res_header.magic_code = 356;
	res_header.cmd = REFRESH;
	res_header.length = Server::getInstance()->getNetwork()->getServer()->_rooms.size();
	_packet.clear();
	_packet << res_header << Server::getInstance()->getNetwork()->getServer()->getRooms();
}

void ParseRequest::start_game()
{
	std::cout << GRN << "[PACKET]" << WHT << " from sender [" << _port << "] to [" << _hostport << "] " << RESET;
	std::cout << CYN << "[REQUEST]" << WHT << "(START_GAME)" << RESET << std::endl;
	Header req_header;
	std::string newuuid;
	if (_packet >> req_header >> newuuid) {
		std::cout << WHT << "[REQUEST] (START_GAME) with parameter: NewUUID[" << newuuid << "]." << RESET << std::endl;
		unsigned short getport = Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->getPlayerbyUUID(newuuid);
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->_players.find(getport)->second->setPort(_port);
		Player *player = Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->getPlayer(getport);
		Player *newplayer = new Player(player);
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->_players.erase(getport);
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->_players[_port] = newplayer;
		Player *test = Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->getPlayer(_port);
		// std::cout << "SIZE _PLAYERS:" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->_players.size() << std::endl;
		// std::cout << "ID:" << test->getID() << "PORT" << test->getPort() << "UUID:" << test->getUUID();
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->_players.find(_port)->second->setConnect(true);	
	}
	_packet.clear();
}

void ParseRequest::nickname()
{
	std::cout << GRN << "[PACKET]" << WHT << " from sender [" << _port << "] to [" << _hostport << "] " << RESET;
	std::cout << CYN << "[REQUEST]" << WHT << "(NICKNAME)" << RESET << std::endl;
	std::string req_username;
	Header req_header;
	if (_packet >> req_header >> req_username) {
		auto it = Server::getInstance()->getNetwork()->getServer()->_players.find(_port);
 		if (it != Server::getInstance()->getNetwork()->getServer()->_players.end())
    		it->second = req_username;
		else
			Server::getInstance()->getNetwork()->getServer()->_players.insert(std::pair<unsigned short, std::string>(_port, req_username));
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = NICKNAME;
		_packet << res_header << OK;
	}
	else {
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = NICKNAME;
		_packet << res_header << ERROR;
	}
}

void ParseRequest::join_room()
{
	std::cout << GRN << "[PACKET]" << WHT << " from sender [" << _port << "] to [" << _hostport << "] " << RESET;
	std::cout << CYN << "[REQUEST]" << WHT << "(JOIN_ROOM)" << RESET << std::endl;
	Header req_header;
	std::string roomName;
	if (_packet >> req_header >> roomName) {
		std::cout << WHT << "[REQUEST] (JOIN_ROOM) with parameter: roomName[" << roomName << "]." << RESET << std::endl;
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = JOIN_ROOM;
		res_header.length = 1;
		unsigned short roomPort = 0;
		roomPort = Server::getInstance()->getNetwork()->getServer()->get_value_from_map(Server::getInstance()->getNetwork()->getServer()->_rooms, roomName);
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->addPlayers(_port, "NaN", _ip);
		std::cout << WHT << "[REQUEST] (JOIN_ROOM) roomPort[" << roomPort << "] : PLAYER(";
		std::cout << "id[" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getID();
		std::cout << "uuid[" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getUUID();
		std::cout << "port[" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getPort();
		std::cout << "x[" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getX();
		std::cout << "y[" << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getY() << ")." << std::endl;
		if (roomPort == 0) {
			std::cout << WHT << "[REQUEST] (JOIN_ROOM) " << RED << "ERROR" << RESET << std::endl;
			_packet.clear();
			Header error_header;
			error_header.magic_code = 356;
			error_header.cmd = JOIN_ROOM;
			error_header.length = 0;
			_packet << error_header << ERROR;
		}
		else {
			_packet << res_header << roomPort << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getID() << Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getPlayer(_port)->getUUID();
		}
	}
	else {
		std::cout << WHT << "[REQUEST] (JOIN_ROOM) " << RED << "ERROR" << RESET << std::endl;
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = JOIN_ROOM;
		res_header.length = 0;
		_packet << res_header << ERROR;
	}
}

unsigned short ParseRequest::get_newPort()
{
	return (_roomPort);
}

bool ParseRequest::get_newRoom()
{
	return (newRoom);
}

void ParseRequest::create_room()
{
	std::cout << CYN << "[REQUEST]" << WHT << "(CREATE_ROOM)" << RESET << std::endl;
	Header req_header;
	std::string roomName;
	if (_packet >> req_header >> roomName) {
		std::cout << WHT << "[REQUEST] (CREATE_ROOM) with parameter: roomName[" << roomName << "]." << RESET << std::endl;
		unsigned short newPort = Server::getInstance()->getNetwork()->getServer()->newRoom();
		Server::getInstance()->getNetwork()->getServer()->addUDPGame(newPort, roomName);
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = CREATE_ROOM;
		res_header.length = Server::getInstance()->getNetwork()->getServer()->_rooms.size();
		_packet << res_header << Server::getInstance()->getNetwork()->getServer()->getRooms();
		newRoom = true;
		_roomPort = newPort;
	}
	else {
		std::cout << WHT << "[REQUEST] (CREATE_ROOM) " << RED << "ERROR" << RESET << std::endl;
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = CREATE_ROOM;
		res_header.length = 0;
		_packet << res_header << ERROR;
	}
}

void ParseRequest::leave_room()
{
	std::cout << CYN << "[REQUEST]" << WHT << "(LEAVE_ROOM)" << RESET << std::endl;
	Header req_header;
	unsigned short roomPort;
	if (_packet >> req_header >> roomPort) {
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = LEAVE_ROOM;
		res_header.length = 0;
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->removePlayers(_port);
		if (Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->getNbrPlayers() == 0) {
			Server::getInstance()->getNetwork()->getServer()->_rooms.find(roomPort)->second->~UDPGame();
			Server::getInstance()->getNetwork()->getServer()->_threads.erase(roomPort);
		}
		_packet << res_header << response::OK;
	}
	else {
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = LEAVE_ROOM;
		res_header.length = 0;
		_packet << res_header << ERROR;
	}
}

void ParseRequest::quit()
{
	std::cout << CYN << "[REQUEST]" << WHT << "(QUIT)" << RESET << std::endl;
}

void ParseRequest::input()
{
	std::cout << CYN << "[REQUEST]" << WHT << "(INPUT)" << RESET << std::endl;
	Header req_header;
	Keyboard req_key;
	int id;
	std::string uuid;
	sf::Packet res = _packet;
	float x;
	float y;
	if (_packet >> req_header >> id >> uuid >> x >> y) {
		std::cout << WHT << "[REQUEST] (INPUT) with parameters: id[" << id << "], uuid[" << uuid << "], x[" << x << "], y[" << y << "]." << RESET << std::endl;
		Server::getInstance()->getNetwork()->getServer()->_rooms.find(_hostport)->second->broadcast(res);
		_packet.clear();
		res.clear();
	}
	else {
		std::cout << WHT << "[REQUEST] (INPUT) " << RED << "ERROR" << RESET << std::endl;
		_packet.clear();
		Header res_header;
		res_header.magic_code = 356;
		res_header.cmd = INPUT;
		res_header.length = 0;
		_packet << res_header << ERROR;
	}
}

void ParseRequest::death()
{
	std::cout << CYN << "[REQUEST]" << WHT << "(DEATH)" << RESET << std::endl;
	Header req_header;
	int id;
	std::string uuid;
	if (_packet >> req_header >> id >> uuid)
		std::cout << RED << "[-]" << WHT << "ITEM with id [" << CYN << id << WHT << "] and uuid[" << CYN << uuid << WHT << "] as been destroyed." << RESET << std::endl;
}