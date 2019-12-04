/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"
#include <dirent.h>

EntityLoader::EntityLoader()
{ 
}

EntityLoader::~EntityLoader()
{
    if (dlclose(this->_handle) != 0)
        std::cerr << dlerror() << std::endl;
}

IEntity *EntityLoader::getInstance() const
{
    IEntity *(*create)();

    create = (IEntity *(*)())dlsym(this->_handle, "create");

    if (!create){
        std::cerr << "dlsym error during instance" << std::endl;
        return (NULL);
    }
    return (create());
}

IEntity *EntityLoader::getInstanceWithHandle(void *handle) const
{
    IEntity *(*create)();

    create = (IEntity *(*)())dlsym(handle, "create");

    if (!create){
        std::cerr << "dlsym error during instance" << std::endl;
        return (NULL);
    }
    return (create());
}

void EntityLoader::getEntityVector()
{
    DIR *dir;
    struct dirent *ent;
    std::string path = "./build/lib/";

    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                path += ent->d_name;
                this->_handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!_handle) {
                    std::cerr << "dlopen error: " << dlerror() << std::endl;
                }
                this->_handleList.push_back(this->_handle);
                this->_pathList.push_back(path);
                path = "./build/lib/";
            }
        }
        closedir(dir);
    } else {
        perror("");
    }     
}

std::vector<std::string> EntityLoader::getPathList()
{
    return (this->_pathList);
}

std::vector<void*> EntityLoader::getHandleList()
{
    return (this->_handleList);
}