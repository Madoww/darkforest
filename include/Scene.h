#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

class SceneBase
{
public:
    virtual void draw(sf::RenderWindow&){};
    virtual void draw_over(sf::RenderWindow&){};
    virtual void update(){};
    virtual ~SceneBase() = default;
};

#endif // SCENE_H
