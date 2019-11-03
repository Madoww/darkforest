#ifndef RAIN_H
#define RAIN_H
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <windows.h>
#include <time.h>
#include <vector>
#include "CameraSystem.h"
#include "Player.h"
/*class Drop : public sf::Drawable, public sf::Transformable
{
public:
private:
};*/

class Rain
{
public:
    Rain();
    virtual ~Rain();
    void rain(sf::RenderWindow& window);
private:
    sf::Vertex drop;
    sf::VertexArray drops;
    float windspeed = 3;
    std::vector<sf::Transform> transform;
    std::vector<sf::RenderStates> states;
    int drops_created = 0;
    CameraSystem& camera = CameraSystem::instance();
    Player& player = Player::instance();
};

#endif // RAIN_H
