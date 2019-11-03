#ifndef ENEMIES_H
#define ENEMIES_H
#include "Enemy.h"
#include <memory>
#include <vector>

class Enemies
{
public:
    static void spawn(std::unique_ptr<Enemy>);
    static void kill(int index);
    static void kill_all();
    static void draw(sf::RenderWindow&);
    static void update();
    static int size(){return enemies.size();}
    static sf::FloatRect getGlobalBounds(int index){return enemies[index]->getGlobalBounds();}
private:
    static std::vector<std::unique_ptr<Enemy>> enemies;
};
#endif // ENEMIES_H
