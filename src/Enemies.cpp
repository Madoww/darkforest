#include "Enemies.h"
#include <iostream>

std::vector<std::unique_ptr<Enemy>> Enemies::enemies = {};

void Enemies::spawn(std::unique_ptr<Enemy> enemy)
{
    enemies.emplace_back(std::move(enemy));
}
void Enemies::kill(int index)
{
    enemies.erase(enemies.begin()+index);
}
void Enemies::kill_all()
{
    enemies.clear();
}
void Enemies::draw(sf::RenderWindow& window)
{
    for(auto& enemy : enemies)
        enemy->draw(window);
}
void Enemies::update()
{
    for(auto& enemy : enemies)
    {
        enemy->agro();
    }
    for(int i = 0; i<enemies.size(); i++)
    {
        for(int j = 0; j<enemies.size(); j++)
        {
            if(enemies[j]->getGlobalBounds().intersects(enemies[i]->getGlobalBounds()) && i!=j)
            {
                std::cout<<"enemies collided"<<std::endl;
                if(enemies[i]->getPosition().x<enemies[j]->getPosition().x)
                    enemies[i]->setPosition(sf::Vector2f(enemies[i]->getPosition().x-3,enemies[i]->getPosition().y));
                else if(enemies[i]->getPosition().x>enemies[j]->getPosition().x)
                    enemies[i]->setPosition(sf::Vector2f(enemies[i]->getPosition().x+3,enemies[i]->getPosition().y));
                enemies[i]->setAgro(false);
            }
        }
        enemies[i]->update();
    }
}
