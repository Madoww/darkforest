#ifndef CLICKCHECK_H
#define CLICKCHECK_H
#include <SFML/Graphics.hpp>

class Click
{
public:
    Click();
    ~Click();
    sf::FloatRect getGlobalBound(){return click.getGlobalBounds();}
    sf::Vector2f getPosition(){return world_pos;}
    static Click& instance(){static Click click; return click;}
    void update(sf::RenderWindow& window);
//private:
    sf::RectangleShape click;
    sf::Vector2i mousePos;
    sf::Vector2f world_pos;
};
class Check
{
public:
    Check(int time);
    virtual ~Check();
    void update();
    void restart();
    inline bool getStatus(){return status;}
    void setDelay(int delay){r2.setPosition(delay,0);}
private:
    sf::RectangleShape r1;
    sf::RectangleShape r2;
    bool status = false;
};

#endif // CLICKCHECK_H
