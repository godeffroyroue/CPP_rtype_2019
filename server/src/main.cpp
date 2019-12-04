/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** main
*/

#include "Server.hpp"

int main(int ac, char **av)
{
    std::srand(time(NULL));
    namespace po = boost::program_options;
    std::string ip = "127.0.0.1";
    unsigned short port = 4141;
    po::options_description desc("Options"); 
    desc.add_options() 
      ("help,h", "Print usage") 
      ("version,v", "Print version information and quit") 
      ("port,p", po::value<unsigned short>(&port), "Set the host Port") 
      ("ip", po::value<std::string>(&ip), "Set the host IP"); 
 
    po::variables_map vm; 
    try { 
      po::store(po::parse_command_line(ac, av, desc),  
                vm); // can throw 
      if (vm.count("help"))  {
        std::cout << "USAGE: ./r-type_server\n" << std::endl;
        std::cout << "A beautiful game for launching a network game\n" << std::endl;
        std::cout << desc << std::endl << std::endl;
        std::cout << "Run './r-type_server COMMAND --help' for more information on a command." << std::endl;
        return (0);
      }
    if (vm.count("version"))  {
        std::cout << "r-type_server version 1.0.1" << std::endl;
        return (0);
      }
      po::notify(vm);
    }
    catch(po::error& e) { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
      return 84; 
    } 
	Server *server = Server::getInstance();
    server->_network = new Network();
    server->_network->_ip = ip;
    server->_network->_port = port;
    server->_network->start();
	return (0);
}