//
//  Effects.hpp
//  dark_forest
//
//  Created by Filip Szafran on 25/06/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Effects_hpp
#define Effects_hpp

#include <SFML/Graphics.hpp>
#include "Player.h"

class Particle
{
public:
    Particle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
    ~Particle(){};
    void move();
    void adjust_speed(float x, float y);
    void setColor(const sf::Color& color){particle.setFillColor(color);}
    void setPosition(const sf::Vector2f& position){particle.setPosition(position);}
    void draw(sf::RenderWindow& window){window.draw(particle);}
    const sf::Vector2f& getPosition(){return particle.getPosition();}
private:
    sf::RectangleShape particle;
    float x,y;
};

class Leafs
{
public:
    ~Leafs(){};
    inline static Leafs& instance()
    {
        static Leafs temp;
        return temp;
    }
    void draw(sf::RenderWindow& window);
private:
    Leafs();
    std::vector<Particle> leafs;
    float speed = Player::instance().speed;
};

#endif /* Effects_hpp */
