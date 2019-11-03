#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include <SFML/Graphics.hpp>
#include "ClickCheck.h"
#include "Flashlight.h"
#include "ClickCheck.h"

struct slow_move_vars
{
    float x,xspeed,yspeed,zoom_amount;
    void restart(){x=0,xspeed=0,yspeed=0,zoom_amount=0;}
};

class CameraSystem
{
public:
    CameraSystem();
    void update();
    inline static CameraSystem& instance()
    {
        static CameraSystem temp;
        return temp;
    }
    const sf::View& getView()const{return view;}
    const sf::View& getDefaultView(){return default_view;}
    void zoom(float);
    void reset(){view.reset(sf::FloatRect(0,0,1920,1080));}
    void move(float x, float y){view.move(x,y);light.move(x,y);offset+=sf::Vector2f(x,y);}
    void slow_move(float x, float xspeed = 1,float yspeed = 0, float zoom_amount = 1);
    const sf::Vector2f& getOffset(){return offset;}
    Check zoom_check;
private:
    sf::View view;
    sf::View default_view;
    Flashlight& light = Flashlight::instance();
    sf::Vector2f offset = sf::Vector2f(0,0);
    Check slow_move_check;
    bool move_slowly = false;
    slow_move_vars smv;
};

#endif // CAMERASYSTEM_H
