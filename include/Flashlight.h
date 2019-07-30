#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "math.h"
#include "ClickCheck.h"

class Flashlight
{
public:
    Flashlight() :
    m_layer(),m_pos(0.f, 0.f)
    {
        m_layer.create(1920, 1080);
        m_flashlightTexture.create(60, 60);

        // We want to have semi-transparent edges.
        generateSpot();

        m_flashlight.setTexture(m_flashlightTexture.getTexture(), true);
        m_flashlight.setPosition(150.f, 150.f);
        m_flashlight.setOrigin(30.f, 30.f);

        m_sprite.setTexture(m_layer.getTexture());
    }
    ~Flashlight();
    void generateSpot()
    {
        m_flashlightTexture.clear();

        // Draw 6 circles with increasing transparency
        for(unsigned int i = 0; i < 6; ++i)
        {
            sf::CircleShape temp(30.f-(i*2.f));
            temp.setOrigin(sf::Vector2f(30.f-(i*2.f), 30.f-(i*2.f)));
            temp.setFillColor(sf::Color(30+(i*10), 30+(i*10), 30+(i*10), 30+(i*10))); //temp.setFillColor(sf::Color(255, 255, 255, 61-(i*10)));
            temp.setPosition(sf::Vector2f(30.f, 30.f));

            m_flashlightTexture.draw(temp, sf::BlendNone);
        }
        m_flashlight.setScale(10,10);
        m_flashlightTexture.display();
    }

    void run(sf::RenderWindow& window,float darkness_level,bool draw_flash)
    {

            // Update the position of the 'flashlight' to the current mouse position
        m_flashlight.setPosition(click.getPosition());

            // Stance-out the 'flashlight' circle
            m_layer.clear(sf::Color(0,0,0,darkness_level));
            m_flashlight.setColor(sf::Color(0,0,0,darkness_level));
            if(draw_flash)
                m_layer.draw(m_flashlight, sf::BlendNone);
            m_layer.display();
            // Draw the layer sprite on top of the 'scene'
            window.draw(m_sprite);
    }
    void setScale(sf::Vector2f player_pos)
    {
            //m_flashlight.setScale((click.getPosition().y)/100 - (float)abs(click.getPosition().x-1000)/300,(click.getPosition().y)/100 - (float)abs(click.getPosition().x-1000)/300);

        if(m_flashlight.getPosition().y<player_pos.y)
        {
        m_flashlight.setScale((float)abs(click.getPosition().y+800-player_pos.y)/100 - (float)abs(click.getPosition().x-player_pos.x)/300,(float)abs(click.getPosition().y+800-player_pos.y)/100 - (float)abs(click.getPosition().x-player_pos.x)/300);
            last_pos = (float)abs(click.getPosition().y+800-player_pos.y)/100;
            if(m_flashlight.getScale().x<=0.2)
                m_flashlight.setScale(0,0);
        }
        else
            m_flashlight.setScale(last_pos-(float)abs(click.getPosition().x-player_pos.x)/300,last_pos-(float)abs(click.getPosition().x-player_pos.x)/300);
    }

private:
    sf::RenderTexture m_flashlightTexture;
    sf::RenderTexture m_layer;
    sf::Sprite m_flashlight;
    sf::Sprite m_sprite;
    sf::Vector2f m_pos;
    Click& click = Click::instance();
    float last_pos;
};

#endif // FLASHLIGHT_H
