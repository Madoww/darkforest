#include "Phone.h"

Phone::Phone()
:flash_check(30),notes_check(30),camera_check(20), messages_check(30),photos_check(30)
{
    phone.setTexture(*TextureManager::get("phone"));
    phone.setScale(scale,scale);
    flash_icon.setSize(sf::Vector2f(10*scale,10*scale));
    flash_icon.setOrigin(flash_icon.getGlobalBounds().width/2,flash_icon.getGlobalBounds().height/2);
    notes_icon = flash_icon;
    camera_icon = flash_icon;
    messages_icon = flash_icon;
    dial_icon = flash_icon;
    photos_icon = flash_icon;
    phone.setPosition(1920-phone.getGlobalBounds().width-20,1080);
    phone_background.setTexture(*TextureManager::get("phone_background"));
    phone_background.setScale(scale,scale);
    menu_bar.setTexture(*TextureManager::get("phone_menu_bar"));
    menu_bar.setScale(5,5);
    menu_bar.setPosition(phone.getPosition());
    camera_background.setTexture(*TextureManager::get("camera_background"));
    camera_background.setScale(5,5);
    back_box.setSize(sf::Vector2f(7*5,5*5));
    lens.setSize(sf::Vector2f(450,300));
    lens.setFillColor(sf::Color(255,255,255,160));
    lens.setOrigin(lens.getSize().x/2,lens.getSize().y/2);
    lens.setPosition(1500,800);

    home_button.setSize(sf::Vector2f(16*scale,5*scale));
    view.setSize(sf::Vector2f(450,300));
    current_view_size = sf::Vector2f(450,300);
    last_pic.setScale(0.14,0.14);
}

Phone::~Phone()
{
    //dtor
}
void Phone::draw(sf::RenderWindow& window)
{
    camera_background.setPosition(phone.getPosition());
    view = window.getView();
    view.setSize(current_view_size);
    view.setCenter(sf::Vector2f(lens.getPosition().x-(225-current_view_size.x/2),lens.getPosition().y-(150-current_view_size.y/2)));
    view.setViewport(sf::FloatRect((phone.getPosition().x+35)/1920, (phone.getPosition().y+110)/1080, 0.095,0.1425));
    if(is_out && camera_status)
    {
        window.draw(lens);
        lens.setPosition(click.getPosition());
        if(lens.getPosition().x+lens.getSize().x/2>1920)
            lens.setPosition(1920-lens.getSize().x/2,click.getPosition().y);
        if(lens.getPosition().x-lens.getSize().x/2<0)
            lens.setPosition(lens.getSize().x/2,click.getPosition().y);
        if(lens.getPosition().y-lens.getSize().y/2<0)
            lens.setPosition(lens.getPosition().x,lens.getSize().y/2);
        if(lens.getPosition().y+lens.getSize().y/2>1080)
            lens.setPosition(lens.getPosition().x,1080-lens.getSize().y/2);
    }
    window.draw(phone_background);
    if(notes_status)
        notes.draw(window,phone.getPosition());
    if(messages_status)
        messages.draw(window, phone.getPosition());
    if(dial_status)
    {
        dial.update();
        dial.draw(window);
    }
    if(photos_status)
    {
        photos.update(sf::Vector2f(phone.getPosition().x+35,phone.getPosition().y+45));
        photos.draw(window);
    }
    if(camera_status)
    {
        window.draw(last_pic);
        window.draw(camera_background);
    }
    if(menu_enabled)
        window.draw(menu_bar);
    window.draw(phone);
}

void Phone::update()
{
    last_pic.setTexture(*photos.getLastPic());
    last_pic.setPosition(phone.getPosition().x+9*scale-10,phone.getPosition().y+57*scale);
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
    photos_icon.setPosition(camera_icon.getPosition().x, dial_icon.getPosition().y);
    home_button.setPosition(phone.getPosition().x+17*scale,phone.getPosition().y+71*scale);
    menu_bar.setPosition(phone.getPosition());
    back_box.setPosition(sf::Vector2f(phone.getPosition().x+11*5,phone.getPosition().y+64*5));
    if(!notes_status && !messages_status && !photos_status && !dial_status)
    {
        toggle_flash();
        toggle_notes();
        toggle_camera();
        toggle_messages();
        toggle_dial();
        toggle_photos();
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
            photos_status = false;
            menu_enabled = false;
        }
    }
    if(last_pic.getGlobalBounds().contains(click.getPosition()) && camera_status)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            camera_status = false;
            photos_status = true;
            photos.open_last_picture();
        }
    }
}
bool Phone::is_back_clicked()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && back_box.getGlobalBounds().contains(click.getPosition()) && menu_enabled)
        return true;
    return false;
}
void Phone::zoom_camera(float zoom)
{
    current_view_size = sf::Vector2f(current_view_size.x*zoom,current_view_size.y*zoom);
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
void Phone::toggle_photos()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(photos_icon.getGlobalBounds().contains(Click::instance().getPosition()) && !photos_status)
        {
            photos.restart_check();
            photos_status = true;
        }
    }
}
