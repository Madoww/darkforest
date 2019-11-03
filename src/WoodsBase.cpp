#include "WoodsBase.hpp"

forest_object::forest_object(const sf::Vector2f& position, float distance, sf::Texture* tex,const sf::Vector2f& window_size_ref)
{
    //srand(time(NULL));
    tree.setTexture(*tex);
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%2+1 == 1)
        {
            tree.setScale(3-distance/4,3);
        }
        else
        {
            tree.setScale(-3+distance/4,3);
            tree.setPosition(tree.getPosition().x+tree.getGlobalBounds().width,tree.getPosition().y);
        }
    }
    else
    {
        tree.setScale(3,3);
    }
    if(tex != TextureManager::get("tree") && tex != TextureManager::get("grass"))
    {
        tree.setScale(5-distance/2,5-distance/2);
    }
    int color = rand()%40;
    tree.setColor(sf::Color(255-color,255-color,255-color));
    //tree.setColor(sf::Color(255-color,255-color,255-color));
    tree.setPosition(position.x-20,window_size_ref.y-tree.getGlobalBounds().height-distance*30-140);
    if(tex == TextureManager::get("tree"))
        tree.setPosition(tree.getPosition().x+100,tree.getPosition().y-20);
    //tree.setColor(sf::Color(tree.getColor().r-distance*23,tree.getColor().g-distance*23,tree.getColor().b-distance*23));
    tree.setPosition(tree.getPosition().x-1000,tree.getPosition().y+200);
    if(tree.getTexture()==TextureManager::get("grass"))
        m_distance = distance;
    else if(tree.getTexture()==TextureManager::get("tree"))
        m_distance = distance+(float)(rand()%20)/10;
    else
        m_distance = distance+2;
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%3==1)
            tree.setTexture(*TextureManager::get("tree2"));
        else
            tree.setTexture(*TextureManager::get("tree3"));
    }
    static sf::Vector2f window_size=window_size_ref;
    default_position = tree.getPosition();
}
void move(movable& object, bool right)
{
    if(right)
        object.move(-Player::instance().speed/object.m_distance*0.92,0);
    else
        object.move(Player::instance().speed/object.m_distance*0.92,0);
}

void forest_object::move(float x, float y)
{
    tree.move(x,y);
}


void forest_object::draw(sf::RenderWindow& window)
{
    window.draw(tree);
}

void ForestObject::draw(sf::RenderWindow& window)
{
    for(auto& obj : objects)
    {
        if(flash.getDrawArea().intersects(obj.getGlobalBounds()))
            obj.draw(window);
    }
}

void ForestObject::add_object(forest_object&& object)
{
    objects.emplace_back(std::move(object));
}
void ForestObject::add_position(float positionx, float positiony)
{
    for(auto& obj : objects)
    {
        obj.setPosition(sf::Vector2f(obj.getPosition().x+positionx,obj.getPosition().y+positiony));
    }
}
void ForestObject::sunset()
{
    int color = rand()%40;
    for(auto& f : objects)
        f.setColor(sf::Color(255-color,80-color,160-color));
}
void ForestObject::loadDefaultForest()
{
    for(int i = 1; i<161; i++)
    {
        add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+1,TextureManager::get("tree"),sf::Vector2f(1600,900)));
        add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+4,TextureManager::get("tree")));
        add_object(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+7,TextureManager::get("tree")));
    }
    for(int i = 0; i<600; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),0.92,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),2,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),3,TextureManager::get("grass")));
    }
    for(int i = 0; i<300; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),4,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),5,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),6,TextureManager::get("grass")));
    }
    for(int i = 0; i<200; i++)
    {
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),7,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),8,TextureManager::get("grass")));
        add_object(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),9,TextureManager::get("grass")));
    }
    sort();
}
void ForestObject::move_forest(int speed)
{
    if(speed>0)
    {
        for(auto& obj : objects)
            move(obj,false);
    }
    else
    {
        for(auto& obj : objects)
            move(obj,true);
    }
}
void ForestObject::update()
{
    if(!player.block_movement){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        for(auto& obj : objects)
            move(obj,false);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        for(auto& obj : objects)
            move(obj,true);
    }
    }
}
