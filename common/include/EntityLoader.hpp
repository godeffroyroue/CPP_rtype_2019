/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EntityLoader
*/


#ifndef ENTITYLOADER_HPP_
#define ENTITYLOADER_HPP_

#include "IEntity.hpp"
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <dlfcn.h>

class EntityLoader {
    public:
        EntityLoader();
        ~EntityLoader();

        IEntity *getInstance() const;
        IEntity *getInstanceWithHandle(void* handle) const;
        void getEntityVector();
        std::vector<void*> getHandleList();
        std::vector<std::string> getPathList();
    
    protected:
        std::string _path;
        void *_handle;
        std::vector<void*> _handleList;
        std::vector<std::string> _pathList;
};   


#endif /* !ENTITYLOADER_HPP_ */




// /*
// ** EPITECH PROJECT, 2019
// ** CPP_rtype_2019
// ** File description:
// ** EntityLoader
// */

// #ifndef ENTITYLOADER_HPP_
// #define ENTITYLOADER_HPP_

// #include "./IEntity.hpp"
// #include <string>
// #include <iostream>
// #include <map>
// #include <functional>

// class EntityLoader {
// 	public:
// 		EntityLoader();
// 		~EntityLoader();

//         IEntity *createEntity(const std::string &id, const int &health);
//         std::map<std::string, std::function<nts::IEntity*(int const&)> > factory;

// 	protected:
//         IEntity *createMechant1(const int &health) const;
//         IEntity *createMechant2(const int &health) const;

// 	private:
// };

// #endif /* !ENTITYLOADER_HPP_ */

