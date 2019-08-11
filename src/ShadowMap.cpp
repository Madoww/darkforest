#include "ShadowMap.h"

ShadowMap::ShadowMap(const std::string& file_name)
{
    file.open(file_name,std::ios::in);
    std::string line;
    std::vector<int> temp_vec;
    while(std::getline(file,line))
    {
        temp_vec.emplace_back(atoi(line.c_str()));
    }
    sf::RectangleShape* temp;
    for(int i = 0; i<temp_vec.size();)
    {
        temp = new sf::RectangleShape;
        temp->setPosition(sf::Vector2f(temp_vec[i],temp_vec[i+1]));
        temp->setSize(sf::Vector2f(temp_vec[i+2],temp_vec[i+3]));
        temp->setFillColor(sf::Color::White);
        default_pos.emplace_back(sf::Vector2f(temp_vec[i],temp_vec[i+1]));
        rects.push_back(temp);
        shadows.push_back(FlashShadow(rects[rects.size()-1],&Click::instance().world_pos));
        i+=4;
    }
}

ShadowMap::~ShadowMap()
{
    //dtor
}
void ShadowMap::update(const sf::Vector2f& position)
{
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        for(auto& rect : rects)
            rect.move(speed,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        for(auto& rect : rects)
            rect.move(-speed,0);*/
    for(int i = 0; i<rects.size(); i++)
    {
        rects[i]->setPosition(sf::Vector2f(position.x+default_pos[i].x,position.y+default_pos[i].y));
        shadows[i].update();
    }
}
void ShadowMap::setPosition(const sf::Vector2f& position)
{
    for(auto& rect : rects)
        rect->setPosition(sf::Vector2f(rect->getPosition().x+position.x,rect->getPosition().y+position.y));
}
void ShadowMap::draw(sf::RenderWindow& window)
{
    for(auto& shadow : shadows)
        shadow.draw(window);
}
