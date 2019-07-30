//
//  Items.h
//  dark_forest
//
//  Created by Filip Szafran on 23/06/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Items_h
#define Items_h
#include <SFML/Graphics.hpp>
#include <vector>
#include "ClickCheck.h"
#include "DialogueSystem.hpp"
#include "Player.h"

class ItemBox
{
public:
    ItemBox(const sf::Vector2f& position, const sf::Vector2f& size,const sf::String& string);
    ~ItemBox(){};
    const sf::FloatRect& getGlobalBounds(){return box.getGlobalBounds();}
    const sf::Vector2f& getPosition(){return box.getPosition();}
    const sf::String& getString(){return string;}
    const sf::Vector2f& getSize(){return box.getSize();}
    void move(float speed){box.move(speed,0);}
    void draw(sf::RenderWindow&);
private:
    sf::RectangleShape box;
    sf::String string;
};

class Items
{
public:
    Items();
    ~Items(){};
    void add_item(const sf::Vector2f& position, const sf::FloatRect& size,const sf::String& string);
    void update(sf::RenderWindow&);
    
    inline static Items& instance()
    {
        static Items temp;
        return temp;
    }
private:
    std::vector<ItemBox> items;
    DialogSystem& dialog = DialogSystem::instance();
    Click& click = Click::instance();
    Player& player = Player::instance();
};

#endif /* Items_h */
