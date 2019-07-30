//
//  Effects.cpp
//  dark_forest
//
//  Created by Filip Szafran on 25/06/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Effects.hpp"

Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White)
{
    particle.setSize(size);
    particle.setPosition(position);
    particle.setFillColor(color);
    x=-rand()%3+1;
    y=rand()%20+5;
    y/=10;
}
void Particle::move()
{
    particle.move(x,y);
}
void Particle::adjust_speed(float x, float y)
{
    particle.move(x,y);
}
Leafs::Leafs()
{
    srand(time(NULL));
    for(int i = 0; i<100; i++)
    leafs.emplace_back(sf::Vector2f(rand()%1920,-600+rand()%1600), sf::Vector2f(5,5),sf::Color(115, 49, 0,120));
    //leafs.emplace_back(sf::Vector2f(rand()%1920,-600+rand()%1600), sf::Vector2f(5,5),sf::Color(20, 80, 20,120));
}
void Leafs::draw(sf::RenderWindow &window)
{
    for(int i = 0; i<leafs.size(); i++)
    {
        leafs[i].move();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            leafs[i].adjust_speed(speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            leafs[i].adjust_speed(-speed, 0);
        leafs[i].draw(window);
        if(leafs[i].getPosition().y>1080)
            leafs[i].setPosition(sf::Vector2f(leafs[i].getPosition().x,-rand()%100));
    }
    
}
