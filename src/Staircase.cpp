//
//  Staircase.cpp
//  dark_forest
//
//  Created by Filip Szafran on 06/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Staircase.hpp"
#include "Player.h"

Staircase::Staircase(int width, int height, int amount_of_steps, bool scale_down)
:width(width),height(height),scale_down(scale_down)
{
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(width,height));
    for(int i = 0; i<amount_of_steps; i++)
    {
        //temp.setPosition(position.x+width*i,position.y-height*i);
        stairs.emplace_back(temp);
    }
}
void Staircase::update(const sf::Vector2f &position)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)&&up==false)
    {
        walk_past = true;
    }
    else
        walk_past = false;
    if(!walk_past)
    for(int i = 0; i<stairs.size(); i++)
    {
        stairs[i].setPosition(position.x+width*i,position.y-height*i);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if(player.getPosition().x>stairs[i].getPosition().x && player.getPosition().x<stairs[i].getPosition().x+stairs[i].getGlobalBounds().width && player.getPosition().y+120>stairs[i].getPosition().y)
        {
            up = true;
            player.setPosition(sf::Vector2f(player.getPosition().x,player.getPosition().y-stairs[i].getGlobalBounds().height));
            if(scale_down)
            {
                player.setScale(2);
                player.setPosition(sf::Vector2f(player.getPosition().x,player.getPosition().y+4));
            }

        }

            }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            if(player.getPosition().x>stairs[i].getPosition().x && player.getPosition().x<stairs[i].getPosition().x+stairs[i].getGlobalBounds().width && player.getPosition().y+120<stairs[i].getPosition().y)
            {
                player.setPosition(sf::Vector2f(player.getPosition().x,player.getPosition().y+height));
                if(i==0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    up = false;
                player.setScale(-2);
                player.setPosition(sf::Vector2f(player.getPosition().x,player.getPosition().y-4));
            }

    }


}
void Staircase::draw(sf::RenderWindow& window)
{
    for(auto& stair: stairs)
        window.draw(stair);
}
