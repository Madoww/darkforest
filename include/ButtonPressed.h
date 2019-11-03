#ifndef BUTTONPRESSED_H
#define BUTTONPRESSED_H
#include <SFML/Graphics.hpp>
#include <iostream>

class ButtonPressed
{
public:
    inline static ButtonPressed& instance()
    {
        ButtonPressed temp;
        return temp;
    }
    static bool buttonPressed(sf::Keyboard::Key key);
    static bool buttonPressed(sf::Mouse::Button button);
private:
    ButtonPressed();
    static bool pressed_once;
};

#endif // BUTTONPRESSED_H
