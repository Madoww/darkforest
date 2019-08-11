//
//  WoodsBase.cpp
//  dark_forest
//
//  Created by Filip Szafran on 07/08/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "WoodsBase.hpp"

forest_object::forest_object(const sf::Vector2f& position, float distance, sf::Texture* tex,const sf::Vector2f& window_size_ref)
{
    //srand(time(NULL));
    tree.setTexture(*tex);
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%2+1 == 1)
        {
            tree.setScale(3-distance/4,3);
        }
        else
        {
            tree.setScale(-3+distance/4,3);
            tree.setPosition(tree.getPosition().x+tree.getGlobalBounds().width,tree.getPosition().y);
        }
    }
    
    
    else
    {
        tree.setScale(3,3);
    }
    if(tex != TextureManager::get("tree") && tex != TextureManager::get("grass"))
    {
        tree.setScale(5-distance/2,5-distance/2);
    }
    int color = rand()%40;
    tree.setColor(sf::Color(255-color,255-color,255-color));
    tree.setPosition(position.x-20,window_size_ref.y-tree.getGlobalBounds().height-distance*30-140);
    if(tex == TextureManager::get("tree"))
        tree.setPosition(tree.getPosition().x+100,tree.getPosition().y-20);
    tree.setColor(sf::Color(tree.getColor().r-distance*16,tree.getColor().g-distance*16,tree.getColor().b-distance*16));
    tree.setPosition(tree.getPosition().x-1000,tree.getPosition().y+200);
    if(tree.getTexture()==TextureManager::get("grass"))
        m_distance = distance;
    else
        m_distance = distance+(float)(rand()%20)/10;
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%3==1)
            tree.setTexture(*TextureManager::get("tree2"));
        else
            tree.setTexture(*TextureManager::get("tree3"));
    }
    static sf::Vector2f window_size=window_size_ref;
    default_position = tree.getPosition();
}
void move(movable& object, bool right)
{
    if(right)
        object.move(-Player::instance().speed/object.m_distance*0.92,0);
    else
        object.move(Player::instance().speed/object.m_distance*0.92,0);
}

void forest_object::move(float x, float y)
{
    tree.move(x,y);
}


void forest_object::draw(sf::RenderWindow& window)
{
    window.draw(tree);
}

void ForestObject::draw(sf::RenderWindow& window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        for(auto& obj : objects)
            move(obj,false);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        for(auto& obj : objects)
            move(obj,true);
    }
    for(auto& obj : objects)
    {
        obj.draw(window);
    }
}

void ForestObject::add_object(forest_object&& object)
{
    objects.emplace_back(std::move(object));
}
void ForestObject::add_position(float position)
{
    for(auto& obj : objects)
    {
        obj.setPosition(sf::Vector2f(obj.getPosition().x,obj.getDefaultPosition().y+position));
    }
}
void ForestObject::loadDefaultForest()
{
    for(int i = 1; i<161; i++)
    {
    add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+1,TextureManager::get("tree"),sf::Vector2f(1600,900)));
        add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+4,TextureManager::get("tree")));
        add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+7,TextureManager::get("tree")));
    }
    for(int i = 0; i<600; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),0.92,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),2,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),3,TextureManager::get("grass")));
    }
    for(int i = 0; i<300; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),4,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),5,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),6,TextureManager::get("grass")));
    }
    for(int i = 0; i<100; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),7,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),8,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),9,TextureManager::get("grass")));
    }
    sort();
}
