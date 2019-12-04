/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** libLoader
*/


#include <iostream>
#include "libLoader.hpp"

LibLoader::LibLoader(const std::string path)
{
    this->_path = path;
    this->_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_handle) {
        std::cerr << dlerror() << std::endl;
    }
}

LibLoader::~LibLoader()
{
    if (dlclose(this->_handle) != 0)
        std::cerr << dlerror() << std::endl;
}

IGfx *LibLoader::getInstance() const
{
    IGfx *(*create)();

    create = (IGfx *(*)())dlsym(this->_handle, "create");

    if (!create){
        std::cerr << "dlsym error during instance" << std::endl;
        return (NULL);
    }
    return (create());
}