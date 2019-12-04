/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** specification
*/

#ifndef SPECIFICATION_HPP_
#define SPECIFICATION_HPP_

#include <vector>
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#define TIME 10

class Spec
{
    public:
        Spec(int id, std::string uid, int damage, bool enemy, int health, sf::Vector2f size, int idShoot, int freqShoot);
        Spec(std::shared_ptr<Spec> &p2);
        ~Spec();
        int getId() const;
        void setUid(std::string uid);
        std::string getUid() const;
        void giveDamage(int damage);
        int getDamage() const;
        bool getIsEnemy() const;
        bool getIsDead() const;
        int getHealth() const;
        sf::Vector2f getSize() const;
        bool getBreak() const;
        void addDuration();
        void setBreak(bool state);
        void addFire();
        void setFire(bool state);
        bool getFire() const;
        int getIdShoot() const;
    private:
        int _id;
        std::string _uid;
        int _damage;
        bool _enemy;
        int _health;
        bool _dead;
        sf::Vector2f _size;
        bool unbreak;
        int duration;
        int _freqShoot;
        int _idShoot;
        bool fire;
        int fire_duration;
};

#endif /* !SPECIFICATION_HPP_ */
