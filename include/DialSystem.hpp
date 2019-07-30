#ifndef DialSystem_hpp
#define DialSystem_hpp

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ClickCheck.h"
#include "Fonts.h"
#include "patch.h"

class DialSystem
{
public:
    void draw(sf::RenderWindow&);
    void setPosition(const sf::Vector2f& position);
    inline static DialSystem& instance()
    {
        static DialSystem temp;
        return temp;
    }
    void enter_number();
private:
    sf::Sprite background, clicked, numbers, call_icon,delete_icon;
    std::vector<sf::RectangleShape> pads;
    sf::RectangleShape temp;
    int pad = 0;
    Fonts font;
    sf::Text number;
    sf::String snumber;
    Click& click = Click::instance();
    Check check;
    Check delete_check;
    int numbers_entered = 0;
    DialSystem();
};

#endif /* DialSystem_hpp */
