//
//  MessagesSystem.hpp
//  dark_forest
//
//  Created by Filip Szafran on 24/06/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef MessagesSystem_hpp
#define MessagesSystem_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include "Fonts.h"
#include "ClickCheck.h"
#include <vector>

class Message
{
public:
    Message(std::string title_string,std::string inside_string, const sf::Vector2f& position);
    Message(){};
    void draw_prev(sf::RenderWindow&, const sf::Vector2f& position);
    void draw_message(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position, sf::Vector2f def_pos);
    sf::Vector2f getPosition(){return background.getPosition();}
    sf::FloatRect getGlobalBounds(){return background.getGlobalBounds();}
    void setFont(const sf::Font& font){title.setFont(font);title.setOrigin(title.getGlobalBounds().width/2,title.getGlobalBounds().height/2);title.setPosition(background.getPosition());
        inside.setFont(font);preview.setFont(font);}
    void move(float x);
    void setStatus(bool status){is_inside = status;}
    bool getStatus(){return is_inside;}
    Fonts font;
private:
    sf::RectangleShape background;
    sf::Text title;
    sf::Text inside;
    sf::Text preview;
    sf::RectangleShape note_background;
    bool is_inside = false;
    int def_note_border = 160;
    int space_position = 0;
};

class MessagesSystem
{
public:
    inline static MessagesSystem& instance()
    {
        static MessagesSystem inst;
        return inst;
    }
    void add_message(sf::String title, sf::String inside);
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow&, const sf::Vector2f& position);
    void restart_messcheck();
    void move(float x);
    bool is_reading = false;
private:
    MessagesSystem();
    Fonts font;
    bool is_set = false;
    sf::Vector2f def_pos;
    std::vector<Message>messages;
    sf::RectangleShape background;
    Check message_open_check;
};

#endif /* MessagesSystem_hpp */
