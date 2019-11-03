#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ClickCheck.h"
#include "Phone.h"
#include "Photos.h"

class Screenshot
{
public:
    Screenshot();
    inline static Screenshot& instance()
    {
        static Screenshot temp;
        return temp;
    }
    void take();
    void take_screenshot(sf::RenderWindow&);
private:
    sf::Image screenshot;
    bool do_take = false;
    int screens_taken = Photos::instance().screens_taken;
    Check screen_check;
    Phone& phone = Phone::instance();
    Photos& photos = Photos::instance();
};

#endif // SCREENSHOT_H
