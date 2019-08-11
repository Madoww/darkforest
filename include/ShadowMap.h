#ifndef SHADOWMAP_H
#define SHADOWMAP_H
#include <fstream>
#include <SFML/Graphics.hpp>
#include "lighting.h"
#include "Player.h"
#include <iostream>
class ShadowMap
{
public:
    ShadowMap(const std::string& file_name);
        ~ShadowMap();
    void draw(sf::RenderWindow&);
    void update(const sf::Vector2f&);
    void setPosition(const sf::Vector2f& position);
private:
    std::fstream file;
    std::vector<sf::RectangleShape*>rects;
    std::vector<sf::Vector2f>default_pos;
    std::vector<FlashShadow>shadows;
    int speed = Player::instance().speed;
};

#endif // SHADOWMAP_H
