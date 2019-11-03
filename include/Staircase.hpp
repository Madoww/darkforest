//
//  Staircase.hpp
//  dark_forest
//
//  Created by Filip Szafran on 06/10/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Staircase_hpp
#define Staircase_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Staircase
{
public:
    Staircase(int width, int height, int amount_of_steps = 1, bool scale_down = false);
    void update(const sf::Vector2f& position);
    void draw(sf::RenderWindow&);
private:
    std::vector<sf::RectangleShape> stairs;
    int width,height;
    Player& player = Player::instance();
    bool up = false;
    bool walk_past = false;
    bool scale_down = false;
};

#endif /* Staircase_hpp */
