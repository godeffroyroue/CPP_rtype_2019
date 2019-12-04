/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** libLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include <dlfcn.h>
#include "IGfx.hpp"

class LibLoader
{
    public:
        LibLoader(std::string path);
        ~LibLoader();
        IGfx *getInstance() const;
    private:
        std::string _path;
        void *_handle;
};

#endif /* !LIBLOADER_HPP_ */
