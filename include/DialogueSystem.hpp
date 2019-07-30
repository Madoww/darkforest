#ifndef DialogueSystem_hpp
#define DialogueSystem_hpp

#include <SFML/Graphics.hpp>
#include "Fonts.h"
#include "ClickCheck.h"
#include <iostream>
#include <string>
#include "Player.h"

class DialogSystem
{
public:
    DialogSystem();
    ~DialogSystem(){};

    void draw(sf::RenderWindow&);

    inline static DialogSystem& instance()
    {
        static DialogSystem temp;
        return temp;
    }
    void setStatus(bool open){is_open = open;}
    DialogSystem& operator=(const DialogSystem&) = delete;
    DialogSystem(const DialogSystem&) = delete;
    void say(const sf::String&);
private:
    sf::RectangleShape background;
    sf::Text text;
    Fonts font;
    int letters_to_draw = 0;
    sf::String string;
    sf::String temp;
    Check letters;
    Check close_check;
    bool is_open = false;
    bool is_saying = false;
    int def_border;
    Player& player = Player::instance();
    sf::Vector2f def_background_size = sf::Vector2f(200,50);
    int b_resize = 0;
};

#endif /* DialogueSystem_hpp */
