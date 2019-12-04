/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <map>

class IEntity {
	public:
	virtual ~IEntity() = default;
        virtual int getHealth() const = 0;
        virtual int getId() const = 0;
        virtual int getDamage() const = 0;
        virtual bool getEnemy() const = 0;
        virtual std::vector<float> getSize() const = 0;
        virtual std::vector<float> getMove() const = 0;
        virtual std::vector<float> getPos() const = 0;
        virtual std::string getTexturePath() const = 0;
        virtual int getOffset() const = 0;
        virtual int getIdShoot() const = 0;
        virtual int getFreqShoot() const = 0;
	private:
};

#endif /* !IENTITY_HPP_ */
