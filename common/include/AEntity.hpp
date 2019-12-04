/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "./IEntity.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <map>

class AEntity : public IEntity {
	public:
		AEntity(int health, int id, int damage, bool enemy, std::vector<float> size, std::vector<float> pos, std::vector<float> move, std::string texture, int offset, int idShoot, int freqShoot);
		virtual ~AEntity() = default;
                virtual int getHealth() const;
                virtual int getId() const;
                virtual int getDamage() const;
                virtual bool getEnemy() const;
                virtual std::vector<float> getSize() const;
                virtual std::vector<float> getPos() const;
                virtual std::vector<float> getMove() const;
                virtual std::string getTexturePath() const;
                virtual int getOffset() const;
                virtual int getIdShoot() const;
                virtual int getFreqShoot() const;
	protected:
                int _health;
                int _id;
                int _damage;
                bool _enemy;
                std::vector<float> _size;
                std::vector<float> _pos;
                std::vector<float> _move;
                std::string _texture;
                int _offset;
                int _idShoot;
                int _freqShoot;
	private:
};

#endif /* !AENTITY_HPP_ */
