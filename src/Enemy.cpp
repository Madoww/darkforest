#include "Enemy.h"
#include <iostream>
#include "TextureManager.h"

Villager::Villager(const sf::Vector2f& position)
{
    rect.setTexture(*TextureManager::get("villager"));
    rect.setScale(5,5);
    rect.setPosition(sf::Vector2f(position.x,position.y-85));
    rect.setOrigin(32,0);
    bounds.setSize(sf::Vector2f(15*rect.getScale().x,55*rect.getScale().y));
    bounds.setPosition(rect.getPosition().x+24*rect.getScale().x-rect.getGlobalBounds().width/2,rect.getPosition().y+8*rect.getScale().y);
    speed = 3;
}
void Villager::draw(sf::RenderWindow& window)
{
    window.draw(rect);
}
void Villager::update()
{
    if(!player.block_movement){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rect.move(player.speed,0);
        bounds.move(player.speed,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rect.move(-player.speed,0);
        bounds.move(-player.speed,0);
    }
    }
    if(is_agro)
    {
        if(player.getPosition().x>rect.getPosition().x)
        {
            rect.setScale(scale,rect.getScale().y);
            rect.move(speed,0);
            bounds.move(speed,0);
        }
        if(player.getPosition().x<rect.getPosition().x)
        {
            rect.setScale(-scale,rect.getScale().y);
            rect.move(-speed,0);
            bounds.move(-speed,0);
        }
    }
}
void Villager::agro()
{
    is_agro = true;
}
