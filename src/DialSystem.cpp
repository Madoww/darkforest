#include "DialSystem.hpp"

DialSystem::DialSystem()
:check(20), delete_check(8)
{
    background.setTexture(*TextureManager::get("dial_background"));
    clicked.setTexture(*TextureManager::get("dial_clicked"));
    numbers.setTexture(*TextureManager::get("dial_numbers"));
    call_icon.setTexture(*TextureManager::get("phone_icon"));
    delete_icon.setTexture(*TextureManager::get("delete_icon"));
    background.setScale(5, 5);
    numbers.setScale(5, 5);
    clicked.setScale(5, 5);
    call_icon.setScale(4, 4);
    delete_icon.setScale(3, 3);
    temp.setSize(sf::Vector2f(50,50));
    temp.setFillColor(sf::Color(200,0,0));
    for(int i = 0; i<9; i++)
        pads.emplace_back(temp);
    int pad = 0;
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            pads[pad].setPosition(background.getPosition().x+5+12*5*i, background.getPosition().y+14*5+12*j);
            pad++;
        }
    }
    number.setFillColor(sf::Color::Black);
    number.setFont(font.font);
    number.setCharacterSize(20);
    number.setString("");
}
void DialSystem::draw(sf::RenderWindow& window)
{
    enter_number();
    window.draw(background);
    window.draw(clicked);
    window.draw(numbers);
    window.draw(number);
    window.draw(call_icon);
    window.draw(delete_icon);
    delete_check.update();
    if(call_icon.getGlobalBounds().contains(click.getPosition()))
        call_icon.setColor(sf::Color(10,150,10));
    else
        call_icon.setColor(sf::Color(255,255,255));
    if(delete_icon.getGlobalBounds().contains(click.getPosition()))
    {
        delete_icon.setColor(sf::Color(180,10,10));
        if(delete_check.getStatus() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && snumber.getSize()>0)
        {
            delete_icon.setColor(sf::Color(120,10,10));
            if(snumber[snumber.getSize()-1]!=sf::String(" "))
                snumber.erase(number.getString().getSize()-1);
            else
            {
                snumber.erase(number.getString().getSize()-1);
                snumber.erase(number.getString().getSize()-2);
            }
            number.setString(snumber);
            --numbers_entered;
            number.setOrigin(number.getGlobalBounds().width/2, number.getGlobalBounds().height/2);
            delete_check.restart();
        }
    }
    else
        delete_icon.setColor(sf::Color(255,255,255));
}
void DialSystem::setPosition(const sf::Vector2f &position)
{
    background.setPosition(sf::Vector2f(position.x+36,position.y+40));
    numbers.setPosition(background.getPosition().x-3,background.getPosition().y-3);
    number.setPosition(background.getPosition().x+background.getGlobalBounds().width/2, background.getPosition().y+50);
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        clicked.setPosition(-60, 0);
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            pads[pad].setPosition(background.getPosition().x+5+12*5*j, background.getPosition().y+12*5*i+14*5);
            pad++;
            if(pad==9)
                pad = 0;
        }
    }
    call_icon.setPosition(pads[6].getPosition().x+5,pads[6].getPosition().y+60);
    delete_icon.setPosition(pads[8].getPosition().x+10,pads[8].getPosition().y+65);
}
void DialSystem::enter_number()
{
    check.update();
    for(int i = 0; i<pads.size(); i++)
    {
        if(check.getStatus() && pads[i].getGlobalBounds().contains(click.getPosition()) && number.getString().getSize()<11)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                number.setString(number.getString()+patch::to_string(i+1));
                number.setOrigin(number.getGlobalBounds().width/2, number.getGlobalBounds().height/2);
                numbers_entered++;
                if(numbers_entered%3==0)
                    number.setString(number.getString()+" ");
                if(i < 3)
                    clicked.setPosition(background.getPosition().x+5+12*5*i,background.getPosition().y+14*5);
                else if(i<6)
                clicked.setPosition(background.getPosition().x+5+12*5*(i-3),background.getPosition().y+14*5+12*5);
                else if(i<9)
                clicked.setPosition(background.getPosition().x+5+12*5*(i-6),background.getPosition().y+14*5+12*5*2);
                snumber = number.getString();
                check.restart();
            }
        }
    }
}
