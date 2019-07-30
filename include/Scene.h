#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

class SceneBase
{
public:
    virtual void draw(sf::RenderWindow&){};
    virtual ~SceneBase() = default;
};

#endif // SCENE_H
