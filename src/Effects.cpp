#include "Effects.hpp"

Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White)
{
    particle.setSize(size);
    particle.setPosition(position);
    particle.setFillColor(color);
    x=-rand()%3+1;
    y=rand()%20+5;
    y/=10;
}
void Particle::move()
{
    particle.move(x,y);
}
void Particle::move_up()
{
    particle.move(x,-y);
}
void Particle::move(float x, float y)
{
    particle.move(x,y);
}
void Particle::adjust_speed(float x, float y)
{
    particle.move(x,y);
}
Leafs::Leafs()
{
    srand(time(NULL));
    for(int i = 0; i<100*4; i++)
    leafs.emplace_back(sf::Vector2f(rand()%1920*4,-600+rand()%1600), sf::Vector2f(5,5),sf::Color(115, 49, 0,120));
    //leafs.emplace_back(sf::Vector2f(rand()%1920,-600+rand()%1600), sf::Vector2f(5,5),sf::Color(20, 80, 20,120));
}
void Leafs::draw(sf::RenderWindow &window)
{
    for(int i = 0; i<leafs.size(); i++)
    {
        leafs[i].move();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            leafs[i].adjust_speed(speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            leafs[i].adjust_speed(-speed, 0);
        leafs[i].draw(window);
        if(leafs[i].getPosition().y>1080)
            leafs[i].setPosition(sf::Vector2f(leafs[i].getPosition().x,-rand()%100));
    }

}
Fire::Fire(const sf::Vector2f& position, int spread, int amount)
:spread(spread),position(position)
{
    srand(time(NULL));
    for(int i = 0; i<spread*amount; i++)
    {
        if(rand()%2==0)
            particles.emplace_back(sf::Vector2f(position.x+rand()%spread,position.y-rand()%100),sf::Vector2f(5,5),sf::Color(116, 20, 14));
        else
            particles.emplace_back(sf::Vector2f(position.x+rand()%spread,position.y-rand()%100),sf::Vector2f(5,5),sf::Color(116, 44, 3));
    }
    
}
void Fire::update()
{
    for(int i = 0; i<particles.size(); i++)
    {
        particles[i].setAlpha(particles[i].getAlpha()-5);
        particles[i].move_up();
        if(particles[i].getAlpha()<5)
        {
            particles[i].setPosition(sf::Vector2f(position.x+rand()%spread,position.y-rand()%100));
            particles[i].setAlpha(rand()%255);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            particles[i].adjust_speed(player.speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            particles[i].adjust_speed(-player.speed, 0);
    }
    if(!player.block_movement){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x+=player.speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x-=player.speed;
    }
}
void Fire::move(float x, float y)
{
    position.x+=x;
    position.y+=y;
    for(auto& p : particles)
    {
        p.adjust_speed(x,0);
    }
}
void Fire::draw(sf::RenderWindow& window)
{
    for(int i = 0; i<particles.size(); i++)
        particles[i].draw(window);
}
