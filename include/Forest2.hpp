//
//  Forest2.hpp
//  dark_forest
//
//  Created by Filip Szafran on 07/08/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Forest2_hpp
#define Forest2_hpp

#include <stdio.h>
#include "Scene.h"
#include "CameraSystem.h"
#include "Player.h"
#include "TextureManager.h"
#include "WoodsBase.hpp"

class Forest2 : public SceneBase
{
public:
    Forest2();
    void draw(sf::RenderWindow&);
    void draw_over(sf::RenderWindow&)override;
private:
    CameraSystem& camera = CameraSystem::instance();
    Player& player = Player::instance();
    int basic_zoom = 0;
    std::vector<sf::Sprite> grass;
    ForestObject forest;
};

#endif /* Forest2_hpp */
