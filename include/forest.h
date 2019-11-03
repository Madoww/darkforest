#ifndef FOREST_H
#define FOREST_H
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include "ClickCheck.h"
#include "InventorySystem.h"
#include "Player.h"
#include "Scene.h"
#include "WoodsBase.hpp"



class Forest : public SceneBase
{
public:
    Forest(int& scene);
    virtual ~Forest();
    void draw(sf::RenderWindow& window)override ;
    void update();
    void resetPosition();
private:
    ForestObject forest;
    sf::Sprite grass;
    sf::RectangleShape path;
    sf::Texture path_tex;
    sf::RectangleShape drawArea;
    sf::Sprite car;
    sf::RectangleShape house;
    sf::RectangleShape roof;
    Check trunk_open;
    Check trunk_status;
    Player& player = Player::instance();
    int sourcex = 0;
    sf::RectangleShape trunk;
    sf::RectangleShape door;
    bool trunkopen = false;
    bool fullyopened = false;
    int& scene;
};

#endif // FOREST_H
