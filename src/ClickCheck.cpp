#include "ClickCheck.h"
#include <iostream>
Check::Check(int time)
{
    r2.setPosition(time,0);
}

Check::~Check()
{
    //dtor
}
void Check::update()
{
    if(r1.getPosition().x!=r2.getPosition().x)
        r1.move(1,0);
    else
        status = true;
}
void Check::restart()
{
    r1.setPosition(0,0);
    status = false;
}

Click::Click()
{
    click.setSize(sf::Vector2f(1,1));
}
Click::~Click()
{
    //dtor
}
void Click::update(sf::RenderWindow& window)
{
    click.setPosition(world_pos);
    mousePos = sf::Mouse::getPosition(window);
    world_pos = window.mapPixelToCoords(mousePos);
}
