#include "ButtonPressed.h"
#include <iostream>
bool ButtonPressed::pressed_once = false;
ButtonPressed::ButtonPressed()
{
    //ctor
}
bool ButtonPressed::buttonPressed(sf::Keyboard::Key key)
{
    if(sf::Keyboard::isKeyPressed(key))
        {
            if(pressed_once == false){
            pressed_once = true;
            return true;}
        }
    else if(!sf::Keyboard::isKeyPressed(key))
        pressed_once = false;
    if(pressed_once)
        return false;
}
bool ButtonPressed::buttonPressed(sf::Mouse::Button button)
{
    if(sf::Mouse::isButtonPressed(button))
        {
            if(pressed_once == false){
            pressed_once = true;
            return true;}
        }
    else if(!sf::Mouse::isButtonPressed(button))
        pressed_once = false;
    if(pressed_once)
        return false;
}
