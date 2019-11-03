#include <stdio.h>
#include "Photos.h"
#include "patch.h"
#include <iostream>
#include "Phone.h"
Photo::Photo(sf::Texture* tex_ptr)
:tex(tex_ptr)
{
    photo.setTexture(*tex_ptr);
    photo.setScale(0.12,0.12);
}
void Photo::draw(sf::RenderWindow& window)
{
    window.draw(photo);
}
Photos::Photos()
:open_check(10)
{
    file.open("Sources/Saves/photos.txt",std::ios::in);
    if(!file.good())
        screens_taken = 24;
    else
    {
        std::string line;
        int line_nr = 1;
        while(std::getline(file,line))
        {
            switch(line_nr)
            {
                case 1: screens_taken = atoi(line.c_str());
                break;
            }
            line_nr++;
        }
        file.close();
    }
    background.setSize(sf::Vector2f(185,330));
    main_photo.setScale(0.4,0.4);
    for(int i = 1; i<screens_taken+1; i++)
    {
        sf::Texture* tex = new sf::Texture;
        tex->loadFromFile("Sources/Sounds/screen"+patch::to_string(i)+".png");
        photos.emplace_back(tex);
    }
    for(int i = 0; i<photos.size(); i++)
    {
        if(i%3==0 && i!=0)
            ypos+=photos[0].getGlobalBounds().height+5;
        photos[i].setPosition(sf::Vector2f(1650+40+photos[0].getGlobalBounds().width*(i%3),20+ypos));
        if(i%3!=0)
            photos[i].setPosition(sf::Vector2f(photos[i].getPosition().x+4*(i%3),photos[i].getPosition().y));
        photos[i].relative_pos = photos[i].getPosition().y;
    }
}
void Photos::update(const sf::Vector2f& position)
{
    background.setPosition(sf::Vector2f(position.x,position.y));
    main_photo.setPosition(sf::Vector2f(position.x,position.y+background.getSize().y/2-main_photo.getGlobalBounds().height/2-25));
    open_check.update();
    for(auto& photo : photos)
    {
        photo.setPosition(sf::Vector2f(photo.getPosition().x,position.y+photo.relative_pos));
        if(open_check.getStatus())
        if(photo.getGlobalBounds().contains(click.getPosition()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !draw_main)
        {
            main_photo.setTexture(*photo.get_texture_ptr());
            draw_main = true;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || Phone::instance().is_back_clicked())
    {
        Phone::instance().disable_menu();
        open_check.restart();
        draw_main = false;
    }
    if(draw_main)
    {
        Phone::instance().enable_menu();
        for(auto& photo : photos)
        {
            if(photo.getAlpha()>50)
                photo.setAlpha(photo.getAlpha()-5);
        }
    }
    else
    {
        for(auto& photo : photos)
        {
            if(photo.getAlpha()<255)
                photo.setAlpha(photo.getAlpha()+5);
        }
    }

    ypos = 20;
}
void Photos::open_last_picture()
{
    main_photo.setTexture(*getLastPic());
    draw_main = true;
}
void Photos::draw(sf::RenderWindow& window)
{
    window.draw(background);
    for(auto& photo : photos)
    {
        if(photo.getPosition().y>background.getPosition().y-photo.getGlobalBounds().height && photo.getPosition().y<background.getPosition().y+background.getGlobalBounds().height-photo.getGlobalBounds().height+10)
            photo.draw(window);
    }
    if(draw_main)
        window.draw(main_photo);
}
void Photos::add_photo(Photo&& photo)
{
    screens_taken++;
    ypos = (photo.getGlobalBounds().height+5)*(photos.size()/3);
    photo.setPosition(sf::Vector2f(1650+40+(photos[0].getGlobalBounds().width+4)*(photos.size()%3),ypos+photos[0].relative_pos));
    photo.relative_pos = photo.getPosition().y;
    photos.push_back(std::move(photo));
}
void Photos::setPosition(const sf::Vector2f& position)
{
    for(int i = 0; i<photos.size(); i++)
    {
        photos[0].setPosition(position);
    }
}
void Photos::scroll_up()
{
    if(!draw_main)
    if(photos[photos.size()-1].getPosition().y>background.getPosition().y+background.getGlobalBounds().height-100)
    {
        for(auto& photo : photos)
            photo.relative_pos-=10;
    }
}
void Photos::scroll_down()
{
    if(!draw_main)
    if(photos[0].getPosition().y<background.getPosition().y+20)
    {
        for(auto& photo : photos)
            photo.relative_pos+=10;
    }
}
Photos::~Photos()
{
    file.open("Sources/Saves/photos.txt",std::ios::out);
    file<<screens_taken<<std::endl;
    file.close();
}
