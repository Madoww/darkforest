//
//  Forest2.cpp
//  dark_forest
//
//  Created by Filip Szafran on 07/08/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Forest2.hpp"

Forest2::Forest2()
{
    sf::Sprite temp;
    temp.setTexture(*TextureManager::get("grass"));
    temp.setScale(3,3);
    for(int i = 0; i<200; i++)
    {
        temp.setPosition(sf::Vector2f(i*64*3,950));
        grass.push_back(temp);
    }
    forest.loadDefaultForest();
    forest.add_position(85);
    forest.add_object(forest_object(sf::Vector2f(2000,0),5,TextureManager::get("booth")));
    forest.sort();
    player.setPosition(sf::Vector2f(player.getPosition().x,1080-215));
}

void Forest2::draw(sf::RenderWindow& window)
{
    forest.draw(window);
}

void Forest2::draw_over(sf::RenderWindow& window)
{
    if(basic_zoom<11)
    {
        camera.zoom(0.99);
        basic_zoom++;
    }
    for(auto& g : grass)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            g.move(player.speed+0.5,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            g.move(-player.speed-0.5,0);
        window.draw(g);
    }
}
