/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IUDPServer
*/

#ifndef IUDPSERVER_HPP_
#define IUDPSERVER_HPP_

class IUDPServer {
	public:
		virtual ~IUDPServer() {};
        virtual void run() = 0;
	protected:
	private:
};

#endif /* !IUDPSERVER_HPP_ */
