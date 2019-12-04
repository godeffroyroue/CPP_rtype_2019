/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include <vector>
#include <iostream>

class IMenu {
    public:
        virtual ~IMenu(){};
        virtual void run() = 0;
        virtual void destroy() = 0;
        virtual bool getStart() const = 0;
        virtual bool getQuit() const = 0;
        virtual int getId() const = 0;
		virtual std::string getUid() const = 0;
        virtual unsigned short getPort() const = 0;

    private:
        bool start = false;
        bool quit = false;

};

#endif /* !IMENU_HPP_ */
