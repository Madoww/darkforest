#include "Screenshot.h"
#include "patch.h"
#include <iostream>

Screenshot::Screenshot()
:screen_check(20)
{
    //ctor
}
void Screenshot::take()
{
    do_take = true;
}
void Screenshot::take_screenshot(sf::RenderWindow& window)
{
    screen_check.update();
    if(do_take || ((sf::Mouse::isButtonPressed(sf::Mouse::Right)) && screen_check.getStatus()))
    {
        screenshot = window.capture();
        sf::Image temp;
        std::vector<sf::Color>colors;
        for(int i = 0; i<450; i++)
        {
            for(int j = 0; j<300; j++)
            {
                colors.emplace_back(screenshot.getPixel(phone.getLensPosition().x+i-225,phone.getLensPosition().y+j-175));
            }
        }
        temp.create(450,300);
        int col = 0;
        for(int i = 0; i<colors.size(); i++)
        {
            colors[i] = sf::Color(colors[i].r+rand()%30,colors[i].g+rand()%30,colors[i].b+rand()%30);
        }
        for(int i = 0; i<450; i++)
        {
            for(int j = 0; j<300; j++)
            {
                temp.setPixel(i,j,colors[col]);
                col++;
            }
        }
        screens_taken++;
        temp.saveToFile("Sources/Sounds/screen"+patch::to_string(screens_taken)+".png");
        do_take = false;
        screen_check.restart();
        sf::Texture* temp_tex = new sf::Texture;
        temp_tex->loadFromFile("Sources/Sounds/screen"+patch::to_string(screens_taken)+".png");
        photos.add_photo(Photo(temp_tex));
    }
}
