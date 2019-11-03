#include "MessagesSystem.hpp"
#include "Phone.h"

Message::Message(std::string title_string,std::string inside_string, const sf::Vector2f& position)
{
    background.setSize(sf::Vector2f(177,50));
    background.setPosition(position);
    title.setCharacterSize(12);
    title.setFillColor(sf::Color::Black);
    title.setString(title_string);
    background.setOrigin(background.getSize().x/2,background.getSize().y/2.5);
    title.setOrigin(title.getGlobalBounds().width/2,title.getGlobalBounds().height/2);
    title.setPosition(background.getPosition());
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);

    inside.setCharacterSize(10);
    inside.setFillColor(sf::Color::Black);
    inside.setString(inside_string);

    preview.setCharacterSize(10);
    preview.setFillColor(sf::Color::Black);
    preview.setOrigin(preview.getGlobalBounds().width/2, preview.getGlobalBounds().height/2);

    sf::String temp;
    for(int i = 0; i<15; i++)
    {
        if(i<inside_string.size())
            temp+=inside_string[i];
    }
    if(temp.getSize()!=inside_string.size())
        temp+="...";
    preview.setString(temp);


    note_background.setSize(sf::Vector2f(185,330));
}
void Message::setPosition(const sf::Vector2f& position, sf::Vector2f def_pos)
{
    background.setPosition(position);
    title.setPosition(background.getPosition().x-70,background.getPosition().y-15);
    preview.setPosition(title.getPosition().x-5,title.getPosition().y+10);
    note_background.setPosition(def_pos.x+35,def_pos.y+45);
    inside.setPosition(note_background.getPosition().x+5,note_background.getPosition().y+15);
}
void Message::draw_prev(sf::RenderWindow& window, const sf::Vector2f& position)
{
    if(background.getPosition().y>position.y+30 && background.getPosition().y<position.y+360)
    {
        window.draw(background);
        window.draw(title);
        window.draw(preview);
    }
}
void Message::draw_message(sf::RenderWindow& window)
{
    if(is_inside == true)
    {

        window.draw(note_background);
        window.draw(inside);
        sf::String temp = inside.getString();
        for(int i = 0; i<inside.getString().getSize(); i++)
        {
            if(inside.findCharacterPos(i).x>note_background.getPosition().x+def_note_border)
            {
                for(int j = i; j>0; j--)
                {
                    if(temp[j]==sf::String(" ") || j==1)
                    {
                        temp.insert(j,"\n");
                        def_note_border+=160;
                        std::cout<<"inserted"<<std::endl;
                        break;
                    }
                }
            }
        }
        inside.setString(temp);
    }
}
void MessagesSystem::add_message(sf::String title, sf::String inside)
{
    messages.emplace_back(Message(title,inside,sf::Vector2f(messages[messages.size()-1].getPosition().x,messages[messages.size()-1].getPosition().y+messages[0].getGlobalBounds().height)));
    messages[messages.size()-1].setFont(font.font);
}
void MessagesSystem::setPosition(const sf::Vector2f& position)
{
    if(is_set == false)
    {
        is_set = true;
        def_pos = position;
    }
    messages[0].setPosition(sf::Vector2f(position.x+messages[0].getGlobalBounds().width/2+35,position.y+messages[0].getGlobalBounds().height/2+50),position);
    for(int i = 1; i<messages.size(); i++)
        messages[i].setPosition(sf::Vector2f(messages[i-1].getPosition().x,messages[i-1].getPosition().y+messages[i-1].getGlobalBounds().height),position);
}
MessagesSystem::MessagesSystem()
:message_open_check(20)
{
    messages.emplace_back(Message("Damn1","kurde belka",sf::Vector2f(200,200)));
    add_message("Mom", "Honey are you okay? Me and dad have been trying to contact you for the past 2 hours. Please text me as soon as you can.");
    messages[0].setFont(font.font);
    background.setSize(sf::Vector2f(185,330));
}

void Message::move(float x)
{
    background.move(0,x);
    title.move(0,x);
}
void MessagesSystem::move(float x)
{
    for(auto& message : messages)
        message.move(x);
}
void MessagesSystem::draw(sf::RenderWindow& window, const sf::Vector2f& position)
{
    background.setPosition(position.x+35,position.y+45);
    if(is_reading)
        Phone::instance().enable_menu();
    else
        Phone::instance().disable_menu();
    message_open_check.update();
    window.draw(background);
    for(int i = 0; i<messages.size(); i++)
    {
        for(int i = 0; i<messages.size(); i++)
        {
            if(messages[i].getStatus())
            {
                is_reading = true;
            }

        }
        if(is_reading == false)
            messages[i].draw_prev(window,position);
        if(messages[i].getGlobalBounds().contains(Click::instance().getPosition()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && message_open_check.getStatus())
        {
            messages[i].setStatus(true);
            message_open_check.restart();
        }
        messages[i].draw_message(window);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || Phone::instance().is_back_clicked())
    {
        is_reading = false;
        for(int i = 0; i<messages.size(); i++)
            messages[i].setStatus(false);
    }
}
void MessagesSystem::restart_messcheck()
{
    message_open_check.restart();
}
