#ifndef PHONE_H
#define PHONE_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ClickCheck.h"
#include "NoteSystem.h"
#include "MessagesSystem.hpp"
#include "DialSystem.hpp"

class Phone
{
public:
    Phone(const Phone&) = delete;
    Phone operator=(const Phone&) = delete;
    virtual ~Phone();
    void draw(sf::RenderWindow&);
    void update();
    inline bool getStatus(){return is_out;}
    inline void setStatus(bool status){is_out=status;}
    inline bool getFlash(){return flash_status;}
    const sf::FloatRect& getGlobalBounds(){return phone.getGlobalBounds();}
    const sf::Vector2f& getPosition(){return phone.getPosition();}
    const sf::FloatRect& getCamera(){if(camera_status)return lens.getGlobalBounds();}
    void turn_off_camera(){camera_status=false;}
    void toggle_flash();
    void toggle_notes();
    void toggle_camera();
    void toggle_messages();
    void toggle_dial();
    void setWindowSize(sf::Vector2f size){window_size=size;}

    inline static Phone& instance()
    {
        static Phone instance;
        return instance;
    }
private:
    Phone();
    bool is_out = false;
    bool flash_status = false;
    bool notes_status = false;
    bool camera_status = false;
    bool messages_status = false;
    bool dial_status = false;
    sf::Sprite phone;
    sf::Sprite phone_background;
    sf::RectangleShape flash_icon;
    sf::RectangleShape notes_icon;
    sf::RectangleShape camera_icon;
    sf::RectangleShape messages_icon;
    sf::RectangleShape dial_icon;
    Check flash_check;
    Check notes_check;
    Check camera_check;
    Check messages_check;

    float scale = 5;
    sf::Vector2f window_size;
    NoteSystem& notes = NoteSystem::instance();
    MessagesSystem& messages = MessagesSystem::instance();
    DialSystem& dial = DialSystem::instance();
    sf::RectangleShape lens;
    sf::RectangleShape home_button;
};

#endif // PHONE_H
