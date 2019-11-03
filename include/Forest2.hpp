#ifndef Forest2_hpp
#define Forest2_hpp

#include <stdio.h>
#include "Scene.h"
#include "CameraSystem.h"
#include "Player.h"
#include "TextureManager.h"
#include "WoodsBase.hpp"
#include "Flashlight.h"
#include "ButtonPressed.h"
#include "Enemies.h"
#include <memory>
#include "Effects.hpp"
#include "Staircase.hpp"

class Forest2 : public SceneBase
{
public:
    Forest2(int& scene);
    void draw(sf::RenderWindow&)override;
    void draw_over(sf::RenderWindow&)override;
    void update()override;
private:
    CameraSystem& camera = CameraSystem::instance();
    Player& player = Player::instance();
    int basic_zoom = 0;
    std::vector<sf::Sprite> grass;
    ForestObject forest;
    sf::Sprite bunker;
    Flashlight& light = Flashlight::instance();
    sf::Sprite lamp;
    float offset = 0;//3500
    int& scene;
    int struggle = 2;
    sf::Sprite cross;
    sf::Sprite cross2;
    bool captured = false;
    Fire cross_fire;
    sf::Sprite house;
    sf::Sprite church;
    Staircase church_stairs;
    Staircase inside_stairs;
    sf::RectangleShape church_inside;
    std::vector<sf::RectangleShape> backs;
};

#endif /* Forest2_hpp */
