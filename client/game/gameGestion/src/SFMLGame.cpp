/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SFMLGame
*/

#include "SFMLGame.hpp"

SFMLGame::SFMLGame()
{
    this->level = 0;
    this->xp = 0;
    this->playerId = -1;
    this->isDone = false;
}

SFMLGame::~SFMLGame()
{
}

bool SFMLGame::addParalax(sf::Vector2f size, sf::Vector2f pos, int speed, std::string path)
{
    std::shared_ptr<paralax_t> first = std::shared_ptr<paralax_t>(new paralax_t);

    first->size = size;
    first->pos = pos;
    first->speed = speed;
    if (!first->texture.loadFromFile(path))
        return (true);
    first->sprite.setTexture(first->texture);
    this->plx.push_back(first);
    return (false);
}

bool SFMLGame::initParalax()
{
    if (addParalax(sf::Vector2f(W * 2, H), sf::Vector2f(0, 0), 1, "client/game/ressources/background/spaceBack.jpg"))
        return (true);
    if (addParalax(sf::Vector2f(W * 2, H), sf::Vector2f(0, 0), 80, "client/game/ressources/background/third_back.png"))
        return (true);
    if (addParalax(sf::Vector2f(W * 2, H), sf::Vector2f(0, 0), 5, "client/game/ressources/background/second_back.png"))
        return (true);
    return (false);

}

bool SFMLGame::initGame(unsigned short port, int id, std::string uid, unsigned short sport, std::string serverIp)
{
    sf::Text waiting;

    this->manager = std::shared_ptr<EntityManager>(new EntityManager());
    this->network = std::shared_ptr<SFMLNetwork>(new SFMLNetwork(serverIp, port, sport));
    this->uid = uid;
    this->id = id;
    this->window.create(sf::VideoMode(W, H), "R-Type");
    this->window.setFramerateLimit(FPS);
    if (!this->font.loadFromFile("client/ressources/Lato-Black.ttf"))
        return (true);
    if (initParalax())
        return (true);
    waiting.setString("Waiting players");
    waiting.setCharacterSize(50);
    waiting.setPosition(W / 2 - 25 * 15/2, H / 2);
    waiting.setFont(this->font);
    this->window.draw(waiting);
    this->window.display();
    this->network->sendStart(uid);
    this->network->getStart(this->manager);
    return (false);
}

void SFMLGame::makeMove(float elapsed)
{
    sf::Vector2f pos;
    bool colected = false;

    for (std::shared_ptr<Entity> ent : this->manager->getCurrent()){
        colected = false;
        for (std::shared_ptr<Entity> tmp: this->manager->getCurrent()){
            if (tmp->getSpec()->getUid() != ent->getSpec()->getUid() && ent->getPhysic()->colision(tmp->getPhysic()->getPos(), tmp->getSpec()->getSize()) && !ent->getSpec()->getBreak()){
                colected = true;
                if (ent->getSpec()->getIsEnemy() == tmp->getSpec()->getIsEnemy() && ent->getSpec()->getIsEnemy() && ent->getSpec()->getIdShoot() == tmp->getSpec()->getIdShoot()){
                    colected = false;
                }
                if (ent->getSpec()->getIsEnemy() != tmp->getSpec()->getIsEnemy()){
                    if (!ent->getSpec()->getIsEnemy()){
                        ent->getSpec()->setBreak(true);
                    }
                    ent->getSpec()->giveDamage(tmp->getSpec()->getDamage());
                }
                break;
            }
        }
        if (!colected || ent->getSpec()->getIdShoot() == -1){
            ent->getPhysic()->makeMove(elapsed, W, H, ent->getSpec()->getIsEnemy(), ent->getSpec()->getIdShoot());
            pos = ent->getPhysic()->getPos();
            ent->getPhysic()->setPos(pos.x, pos.y);
            ent->getGraph()->setPosition(pos.x, pos.y);
        }
    }
}

void SFMLGame::displayInfo(std::shared_ptr<Entity> player)
{
    sf::Text health;
    health.setString(std::to_string(player->getSpec()->getHealth()) + " PV");
    health.setCharacterSize(20);
    health.setFont(this->font);
    health.setPosition(30, 30);
    this->window.draw(health);

    sf::Text nb ;
    nb.setString("Player: "+ std::to_string(player->getSpec()->getId()));
    nb.setCharacterSize(20);
    nb.setFont(this->font);
    nb.setPosition(30, 50);
    this->window.draw(nb);
}

void SFMLGame::displayParalax()
{
    for (std::shared_ptr<paralax_t> p : this->plx){
        p->sprite.setTexture(p->texture);
        p->sprite.setPosition(p->pos.x, p->pos.y);
        this->window.draw(p->sprite);
        p->pos.x -= p->speed;
        if (p->pos.x * -1 >= p->size.x / 2){
            p->pos.x = 0;
        }
    }
}

void SFMLGame::display()
{
    window.clear(sf::Color::Black);
    displayParalax();
    for (std::shared_ptr<Entity> ent : this->manager->getCurrent()){
        ent->getGraph()->display(this->window);
        if (ent->getSpec()->getId() == this->id)
            displayInfo(ent);
    }
    window.display();
}

void SFMLGame::destroy()
{
    this->window.close();
}

std::shared_ptr<Entity> SFMLGame::getPlayer()
{
    std::vector<std::shared_ptr<Entity>> tmp = this->manager->getCurrent();
    for (size_t i = 0; i < tmp.size(); i++){
        if (tmp[i]->getSpec()->getId() == this->id){
            return (tmp[i]);
        }
    }
    return (NULL);
}

void SFMLGame::checkUnbreak()
{
    for (std::shared_ptr<Entity> ent : this->manager->getCurrent()){
        if (ent->getSpec()->getBreak()){
            ent->getSpec()->addDuration();
        }
    }
}

bool SFMLGame::checkDeath()
{
    bool state = true;
    std::shared_ptr<Entity> p = getPlayer();

    while (state){
        state = false;
        for (std::shared_ptr<Entity> ent : this->manager->getCurrent()){
            if (ent->getSpec()->getIsDead()){
                if (ent->getSpec()->getIsEnemy() && ent->getSpec()->getIdShoot() != -1){
                    this->network->sendDeath(ent->getSpec()->getId(), ent->getSpec()->getUid());
                }
                if (ent->getSpec()->getId() == this->id && ent->getSpec()->getUid() == this->uid){
                    this->network->sendDeath(ent->getSpec()->getId(), ent->getSpec()->getUid());
                    return (true);
                }
                this->manager->removeEntity(ent->getSpec()->getUid());
                state = true;
                break;
            }
            if (ent->getPhysic()->getPos().x + ent->getSpec()->getSize().x < 0){
                this->manager->removeEntity(ent->getSpec()->getUid());
                state = true;
                break;
            }
            if (ent->getPhysic()->getPos().x > W && !ent->getSpec()->getIsEnemy()){
                this->manager->removeEntity(ent->getSpec()->getUid());
                state = true;
                break;
            }
        }
    }
    return (false);
}

void SFMLGame::keyManagement(sf::Event event)
{
    std::shared_ptr<Entity> p = getPlayer();
    sf::Vector2f pos = p->getPhysic()->getPos();
    sf::Vector2f size = p->getSpec()->getSize();
    if (event.key.code == sf::Keyboard::Left && pos.x > 0){
        p->getPhysic()->setPos(pos.x - MOVING, pos.y);
        this->network->sendPos(p->getSpec()->getId(), p->getSpec()->getUid(), pos.x - MOVING, pos.y);
    }
    if (event.key.code == sf::Keyboard::Right && pos.x + size.x < W){
        p->getPhysic()->setPos(pos.x + MOVING, pos.y);
        this->network->sendPos(p->getSpec()->getId(), p->getSpec()->getUid(), pos.x + MOVING, pos.y);
    }
    if (event.key.code == sf::Keyboard::Up && pos.y > 0){
        p->getPhysic()->setPos(pos.x, pos.y - MOVING);
        this->network->sendPos(p->getSpec()->getId(), p->getSpec()->getUid(), pos.x, pos.y - MOVING);
    }
    if (event.key.code == sf::Keyboard::Down && pos.y + size.y < H){
        p->getPhysic()->setPos(pos.x, pos.y + MOVING);
        this->network->sendPos(p->getSpec()->getId(), p->getSpec()->getUid(), pos.x, pos.y + MOVING);
    }
    if (event.key.code == sf::Keyboard::Space && p->getSpec()->getFire()){
        p->getSpec()->setFire(false);
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        this->network->sendPos(p->getSpec()->getIdShoot(), (boost::lexical_cast<std::string>(uuid)), pos.x + size.x + 10, pos.y + size.y / 2);
    }
}

void SFMLGame::eventHandling(sf::Event event)
{
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed){
            keyManagement(event);
        }
    }
}

void SFMLGame::enemyShoot()
{
    for (std::shared_ptr<Entity> ent : this->manager->getCurrent()){
        if (ent->getSpec()->getUid() == this->uid && ent->getSpec()->getId() == this->id){
            if (!ent->getSpec()->getFire()){
                ent->getSpec()->addFire();
            }                
        }
        if (ent->getSpec()->getIsEnemy() && ent->getSpec()->getIdShoot() != -1){
            if (ent->getSpec()->getFire()){
                boost::uuids::uuid uuid = boost::uuids::random_generator()();
                sf::Vector2f pos = ent->getPhysic()->getPos();
                sf::Vector2f size = ent->getSpec()->getSize();
                pos.x = pos.x - 50;
                pos.y += size.y / 2;
                this->manager->addEntity(ent->getSpec()->getIdShoot(), (boost::lexical_cast<std::string>(uuid)), pos);
                ent->getSpec()->setFire(false);
            }
            else
                ent->getSpec()->addFire();
        }
    }
}

void SFMLGame::startUpdate()
{
    network->update(this->manager, this->id, this->uid);
}

void SFMLGame::startGame()
{
    sf::Clock clock;
    sf::Time elapsed;
    float time = 0;

    sf::Thread td (&SFMLGame::startUpdate, this);
    td.launch();
    while (window.isOpen() && !this->isDone) {
        elapsed = clock.getElapsedTime();
        clock.restart();
        time += elapsed.asSeconds();
        sf::Event event;
        eventHandling(event);
        if (time > 0.2){
            checkUnbreak();
            enemyShoot();
            time = 0;
        }
        if (time > 0.05){
            makeMove(elapsed.asMilliseconds() / 16 + 1);
            display();
        }
        if (checkDeath())
            break;
    }
    td.terminate();
    std::cout << "game ended" << std::endl;
}
