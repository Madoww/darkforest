#ifndef WoodsBase_hpp
#define WoodsBase_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Player.h"
#include "Timer.hpp"
#include "Flashlight.h"

struct movable
{
    virtual void move(float x, float y) = 0;
    float m_distance = 1;
    virtual ~movable(){}
};
void move(movable&, bool right);

class forest_object : public movable
{
public:
    forest_object(const sf::Vector2f& position, float distance, sf::Texture* tex,const sf::Vector2f& window_size_ref = sf::Vector2f(1600,900));
    void draw(sf::RenderWindow& window);
    void move (float x, float y) override;
    bool operator<(const forest_object& other)const{return m_distance>other.m_distance;}
    sf::FloatRect getGlobalBounds(){return tree.getGlobalBounds();}
    sf::Vector2f getPosition(){return tree.getPosition();}
    float getDistance(){return m_distance;}
    bool is_tree(){return tree.getTexture()==TextureManager::get("tree");}
    void setPosition(const sf::Vector2f& position){tree.setPosition(position);}
    sf::Vector2f getDefaultPosition(){return default_position;}
    void setColor(sf::Color color){tree.setColor(color);}
private:
    sf::Sprite tree;
    sf::Vector2f default_position;
    //static sf::Vector2f window_size;
};

class ForestObject
{
public:
    void draw(sf::RenderWindow&);
    void update();
    void sunset();
    void add_object(forest_object&&);
    void sort(){std::sort(objects.begin(),objects.end());}
    void add_position(float positionx, float positiony = 0);
    void move_forest(int speed);
    void loadDefaultForest();
private:
    Player& player = Player::instance();
    std::vector<forest_object> objects;
    Flashlight& flash = Flashlight::instance();
};

#endif /* WoodsBase_hpp */
