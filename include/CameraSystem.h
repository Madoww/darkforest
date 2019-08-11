#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include <SFML/Graphics.hpp>
#include "ClickCheck.h"


class CameraSystem
{
public:
    CameraSystem();
    inline static CameraSystem& instance()
    {
        static CameraSystem temp;
        return temp;
    }
    const sf::View& getView()const{return view;}
    const sf::View& getDefaultView(){return default_view;}
    void zoom(float);
    void reset(){view.reset(sf::FloatRect(0,0,1920,1080));}
    Check zoom_check;
private:
    sf::View view;
    sf::View default_view;
};

#endif // CAMERASYSTEM_H
