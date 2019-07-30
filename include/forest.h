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

struct movable
{
    virtual void move(float x, float y) = 0;
    float m_distance = 1;
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
private:
    sf::Sprite tree;
    //static sf::Vector2f window_size;
};

class Bush : public movable
{
public:
    Bush(int position, float distance);
    void draw(sf::RenderWindow& window);
    void move (float x, float y) override;
private:
    sf::Sprite bush;
};

class Forest : public SceneBase
{
public:
    Forest(int& scene);
    virtual ~Forest();
    void draw(sf::RenderWindow& window)override ;

private:
    std::vector<forest_object>objects;
    std::vector<Bush>bushes;
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
