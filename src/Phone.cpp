#include "Phone.h"

Phone::Phone()
:flash_check(30),notes_check(30),camera_check(20), messages_check(30)
{
    phone.setTexture(*TextureManager::get("phone"));
    phone.setScale(scale,scale);
    flash_icon.setSize(sf::Vector2f(10*scale,10*scale));
    flash_icon.setOrigin(flash_icon.getGlobalBounds().width/2,flash_icon.getGlobalBounds().height/2);
    notes_icon = flash_icon;
    camera_icon = flash_icon;
    messages_icon = flash_icon;
    dial_icon = flash_icon;
    phone.setPosition(1920-phone.getGlobalBounds().width-20,1080);

    phone_background.setTexture(*TextureManager::get("phone_background"));
    phone_background.setScale(scale,scale);
    lens.setSize(sf::Vector2f(450,300));
    lens.setFillColor(sf::Color(255,255,255,160));
    lens.setOrigin(lens.getSize().x/2,lens.getSize().y/2);

    home_button.setSize(sf::Vector2f(16*scale,5*scale));
}

Phone::~Phone()
{
    //dtor
}

void Phone::draw(sf::RenderWindow& window)
{
    if(is_out && camera_status)
    {
        window.draw(lens);
        lens.setPosition(Click::instance().getPosition());
    }
    window.draw(phone_background);
    if(notes_status)
        notes.draw(window,phone.getPosition());
    if(messages_status)
        messages.draw(window, phone.getPosition());
    if(dial_status)
        dial.draw(window);
    window.draw(phone);
}

void Phone::update()
{
    phone_background.setPosition(phone.getPosition());
    flash_check.update();
    notes_check.update();
    camera_check.update();
    messages_check.update();
    flash_icon.setPosition(phone.getPosition().x+14*scale,phone.getPosition().y+17*scale);
    notes_icon.setPosition(flash_icon.getPosition().x+11*scale,flash_icon.getPosition().y);
    camera_icon.setPosition(notes_icon.getPosition().x+11*scale,notes_icon.getPosition().y);
    messages_icon.setPosition(flash_icon.getPosition().x, flash_icon.getPosition().y+11*scale);
    dial_icon.setPosition(notes_icon.getPosition().x, messages_icon.getPosition().y);
    home_button.setPosition(phone.getPosition().x+17*scale,phone.getPosition().y+71*scale);
    if(!notes_status && !messages_status)
    {
        toggle_flash();
        toggle_notes();
        toggle_camera();
        toggle_messages();
        toggle_dial();
    }
    notes.setPosition(sf::Vector2f(phone.getPosition().x,phone.getPosition().y));
    messages.setPosition(sf::Vector2f(phone.getPosition().x,phone.getPosition().y));
    dial.setPosition(phone.getPosition());
    if(is_out)
    {
        
        if(phone.getPosition().y>1080-phone.getGlobalBounds().height-10)
        {
            //notes.setPosition(sf::Vector2f(phone.getPosition().x,phone.getPosition().y-10));
            phone.move(0,-10);
        }
    }
    else
    {
        if(phone.getPosition().y<1080)
        {
            //notes.setPosition(sf::Vector2f(phone.getPosition().x,phone.getPosition().y-10));
            phone.move(0,10);
        }
    }
    if((home_button.getGlobalBounds().contains(Click::instance().getPosition())&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        {
            notes_status = false;
            camera_status = false;
            messages_status = false;
            dial_status = false;
        }
    }
}
void Phone::toggle_flash()
{
    if(flash_icon.getGlobalBounds().contains(Click::instance().getPosition()))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(flash_check.getStatus())
            {
                if(flash_status)
                {
                    flash_status = false;
                    std::cout<<"Flashlight turned off\n";
                }

                else
                {
                    flash_status = true;
                    std::cout<<"Flashlight turned on\n";
                }

                flash_check.restart();
            }
        }
    }
}
void Phone::toggle_notes()
{
    if(notes_icon.getGlobalBounds().contains(Click::instance().getPosition()))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(notes_check.getStatus())
            {
                {
                    notes_status = true;
                    notes.restart_notecheck();
                    std::cout<<"Notes turned on\n";
                }
                notes_check.restart();
            }
        }
    }
}
void Phone::toggle_camera()
{
    if(camera_icon.getGlobalBounds().contains(Click::instance().getPosition()))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(camera_check.getStatus())
            {
                if(camera_status)
                {
                    camera_status = false;
                    std::cout<<"Camera turned off\n";
                }
                else
                {
                    camera_status = true;
                    std::cout<<"Camera turned on\n";
                }
                camera_check.restart();
            }
        }
    }
}
void Phone::toggle_messages()
{
    if(messages_icon.getGlobalBounds().contains(Click::instance().getPosition()))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(messages_check.getStatus())
            {
                if(messages_status)
                {
                    messages_status = false;
                    std::cout<<"Messages turned off\n";
                }
                
                else
                {
                    messages_status = true;
                    messages.restart_messcheck();
                    std::cout<<"Messages turned on\n";
                }
                messages_check.restart();
            }
        }
    }
}
void Phone::toggle_dial()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(dial_icon.getGlobalBounds().contains(Click::instance().getPosition()))
        {
            dial_status = true;
        }
    }
}
