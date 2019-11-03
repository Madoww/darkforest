#ifndef PHONE_H
#define PHONE_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ClickCheck.h"
#include "NoteSystem.h"
#include "MessagesSystem.hpp"
#include "DialSystem.hpp"
#include "Photos.h"

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
    void toggle_photos();
    void setWindowSize(sf::Vector2f size){window_size=size;}
    void enable_menu(){menu_enabled = true;}
    void disable_menu(){menu_enabled = false;}
    bool is_back_clicked();
    bool getPhotosStatus(){return photos_status;}
    bool getCameraStatus(){return camera_status;}
    bool getNotesStatus(){return notes_status;}
    sf::Vector2f getLensPosition(){return lens.getPosition();}
    void zoom_camera(float zoom);

    inline static Phone& instance()
    {
        static Phone instance;
        return instance;
    }
    sf::View view;
private:
    Phone();
    bool is_out = false;
    bool flash_status = false;
    bool notes_status = false;
    bool camera_status = false;
    bool messages_status = false;
    bool dial_status = false;
    bool photos_status = false;
    bool menu_enabled = false;
    sf::Sprite phone;
    sf::Sprite phone_background;
    sf::RectangleShape flash_icon;
    sf::RectangleShape notes_icon;
    sf::RectangleShape camera_icon;
    sf::RectangleShape messages_icon;
    sf::RectangleShape dial_icon;
    sf::RectangleShape photos_icon;
    Check flash_check;
    Check notes_check;
    Check camera_check;
    Check messages_check;
    Check photos_check;
    sf::Vector2f current_view_size;

    float scale = 5;
    sf::Vector2f window_size;
    Click& click = Click::instance();
    NoteSystem& notes = NoteSystem::instance();
    MessagesSystem& messages = MessagesSystem::instance();
    DialSystem& dial = DialSystem::instance();
    Photos& photos = Photos::instance();
    sf::RectangleShape lens;
    sf::RectangleShape home_button;
    sf::RectangleShape back_box;
    sf::Sprite menu_bar;
    sf::Sprite camera_background;
    sf::Sprite last_pic;
};

#endif // PHONE_H
