#ifndef SHED_H
#define SHED_H
#include "ClickCheck.h"
#include "InventorySystem.h"
#include "TextureManager.h"
#include "Scene.h"
#include "lighting.h"
#include "Player.h"
#include "CameraSystem.h"
#include "DialogueSystem.hpp"

class Cross
{
public:
    Cross(const sf::Vector2f& position)
    {
        cross.setTexture(*TextureManager::get("cross"));
        cross.setPosition(position);
        cross.setScale(8,8);
        cross.setColor(sf::Color(100,100,100));
        cross.setOrigin(1.5,2.5);
    }
    void draw(sf::RenderWindow& window);
    void tilt();
    sf::FloatRect getGlobalBounds(){return cross.getGlobalBounds();}
    void move(float x, float y){cross.move(x,y);}
    static int tilted_amount;
private:
    sf::Sprite cross;
    bool added = false;
    bool is_tilted = false;
};

class Shed : public SceneBase
{
public:
    Shed();
    virtual ~Shed();
    void draw(sf::RenderWindow& window)override;
private:
    sf::Sprite background;
    sf::RectangleShape hatch;
    Check hatch_check;
    Check blood_check;
    Check wait_for_blood;
    bool open_hatch;
    int sourcex = 0;
    int bloodx = 0;
    sf::Sprite painting;
    sf::RectangleShape s1;
    sf::RectangleShape s2;
    Shadow shadow1;
    Shadow shadow2;
    std::vector<Cross>crosses;
    Player& player = Player::instance();
    sf::Sprite blood;
    sf::Vector2f falling_speed = sf::Vector2f(-2,-9.2);
    CameraSystem& camera = CameraSystem::instance();
    sf::Sprite basement;
    sf::Sprite corridor;
    sf::RectangleShape door;
    bool is_tilted = false;
    bool in_basement = false;
};

#endif // SHED_H
