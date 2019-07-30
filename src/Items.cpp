//
//  Items.cpp
//  dark_forest
//
//  Created by Filip Szafran on 23/06/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include <stdio.h>
#include "Items.h"

ItemBox::ItemBox(const sf::Vector2f& position, const sf::Vector2f& size,const sf::String& string)
:string(string)
{
    box.setSize(size);
    box.setPosition(position);
}
void ItemBox::draw(sf::RenderWindow& window)
{
    window.draw(box);
}
Items::Items()
{
    
}
void Items::add_item(const sf::Vector2f& position, const sf::FloatRect& size,const sf::String& string)
{
    items.emplace_back(ItemBox(position,sf::Vector2f(size.width,size.height),string));
}
void Items::update(sf::RenderWindow& window)
{
    for(auto& item : items)
    {
        //item.draw(window);
        if(item.getPosition().x<click.getPosition().x && click.getPosition().x<item.getPosition().x+item.getSize().x && click.getPosition().y>item.getPosition().y && click.getPosition().y<item.getPosition().y+item.getSize().y && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            dialog.say(item.getString());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            item.move(player.speed);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            item.move(-player.speed);
    }
}
