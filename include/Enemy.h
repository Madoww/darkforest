#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "math.h"
#include <iostream>


class Enemy
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void agro() = 0;
    virtual sf::FloatRect getGlobalBounds(){return bounds.getGlobalBounds();}
    virtual void setAgro(bool agro){is_agro = agro;}
    virtual void setPosition(const sf::Vector2f& pos){rect.setPosition(pos);bounds.setPosition(rect.getPosition().x+24*abs(rect.getScale().x)-rect.getGlobalBounds().width/2,rect.getPosition().y+8*abs(rect.getScale().y));}
    virtual sf::Vector2f getPosition(){return rect.getPosition();}
    virtual ~Enemy(){};
protected:
    sf::Sprite rect;
    sf::RectangleShape bounds;
    Player& player = Player::instance();
    int speed;
    bool is_agro = false;
};

class Villager : public Enemy
{
public:
    Villager(const sf::Vector2f& position);
    ~Villager(){std::cout<<"Destroyed"<<std::endl;}
    void draw(sf::RenderWindow& window)override;
    void update()override;
    void agro()override;
private:
    int scale = 5;
};

#endif // ENEMY_H
