#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "math.h"
#include "ClickCheck.h"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"

class LightSource
{
public:
    LightSource(const sf::Vector2f& position, const sf::Vector2f& size, bool dynamic, int grow_distance)
    :m_dynamic(dynamic),grow_distance(grow_distance)
    {
        m_flashlightTexture.create(60, 60);
        
        generateSpot();
        
        light.setTexture(m_flashlightTexture.getTexture(), true);
        light.setPosition(position);
        light.setOrigin(30.f, 30.f);
        light.setScale(size);
        default_size = size;
    }
    LightSource(const LightSource&){};
    void generateSpot()
    {
        m_flashlightTexture.clear();
        
        // Draw 6 circles with increasing transparency
        for(unsigned int i = 0; i < 15; ++i)
        {
            sf::CircleShape temp(30.f-(i*2.f));
            temp.setOrigin(sf::Vector2f(30.f-(i*2.f), 30.f-(i*2.f)));
            //temp.setFillColor(sf::Color(30+(i*10), 30+(i*10), 30+(i*10), 30+(i*10))); //temp.setFillColor(sf::Color(255, 255, 255, 61-(i*10)));
            temp.setFillColor(sf::Color(255-i*17,255-i*17,255-i*17,255-i*17));
            temp.setPosition(sf::Vector2f(30.f, 30.f));
            
            m_flashlightTexture.draw(temp, sf::BlendNone);
        }
        m_flashlightTexture.display();
    }
    void update()
    {
        if(grow)
        {
            light.setScale(light.getScale().x+0.1*(default_size.x+default_size.x/grow_distance-light.getScale().x+0.1), light.getScale().y+0.1*(default_size.x+default_size.x/grow_distance-light.getScale().x+0.1));
        }
        else
            light.setScale(light.getScale().x-0.1*(light.getScale().x-default_size.x+default_size.x/grow_distance-0.1), light.getScale().y-0.1*(light.getScale().x-default_size.x+default_size.x/grow_distance-0.1));
        if(light.getScale().x>default_size.x+default_size.x/grow_distance)
            grow = false;
        if(light.getScale().x<default_size.x)
            grow = true;
    }
    sf::Sprite& getSource(){return light;}
    bool is_dynamic(){return m_dynamic;}
    int grow_distance;
private:
    sf::Sprite light;
    sf::RenderTexture m_flashlightTexture;
    bool m_dynamic;
    sf::Vector2f default_size;
    bool grow = false;
};

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
        for(unsigned int i = 0; i < 30; ++i)
        {
            sf::CircleShape temp(30.f-(i*1.f));
            temp.setOrigin(sf::Vector2f(30.f-(i*1.f), 30.f-(i*1.f)));
            //temp.setFillColor(sf::Color(30+(i*10), 30+(i*10), 30+(i*10), 30+(i*10))); //temp.setFillColor(sf::Color(255, 255, 255, 61-(i*10)));
                    //temp.setFillColor(sf::Color(255-i*21.25,255-i*21.25,255-i*21.25,255-i*21.25));
                temp.setFillColor(sf::Color(255-i*8.5,255-i*8.5,255-i*8.5,255-i*8.5));
            temp.setPosition(sf::Vector2f(30.f, 30.f));

            m_flashlightTexture.draw(temp, sf::BlendNone);
        }
        darkness_level = 100;
        m_flashlight.setScale(10,10);
        m_flashlightTexture.display();
    }

    void run(sf::RenderWindow& window,bool draw_flash)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            for(auto& src : sources)
            {
                src->getSource().move(Player::instance().speed,0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            for(auto& src : sources)
            {
                src->getSource().move(-Player::instance().speed,0);
            }
        }
            // Update the position of the 'flashlight' to the current mouse position
        m_flashlight.setPosition(click.getPosition());

            // Stance-out the 'flashlight' circle
            m_layer.clear(sf::Color(0,0,0,darkness_level));
            m_flashlight.setColor(sf::Color(0,0,0,darkness_level));
            for(auto& src : sources)
            {
                src->getSource().setColor(sf::Color(0,0,0,darkness_level));
                if(src->is_dynamic())
                    src->update();
                //src->getSource().setPosition(click.getPosition());
            }
            for(auto& src : sources)
                m_layer.draw(src->getSource(),sf::BlendNone);
            if(draw_flash)
            {
                m_layer.draw(m_flashlight, sf::BlendNone);
            }
            m_layer.display();
            // Draw the layer sprite on top of the 'scene'
            window.draw(m_sprite);
    }
    static void setLevel(float level)
    {
        darkness_level=level;
    }
    void setScale(sf::Vector2f player_pos)
    {
            //m_flashlight.setScale((click.getPosition().y)/100 - (float)abs(click.getPosition().x-1000)/300,(click.getPosition().y)/100 - (float)abs(click.getPosition().x-1000)/300);

        if(m_flashlight.getPosition().y<player_pos.y)
        {
        m_flashlight.setScale((float)abs(click.getPosition().y+800-player_pos.y)/100 - (float)abs(click.getPosition().x-player_pos.x)/200,(float)abs(click.getPosition().y+800-player_pos.y)/100 - (float)abs(click.getPosition().x-player_pos.x)/200);
            last_pos = (float)abs(click.getPosition().y+800-player_pos.y)/100;
            if(m_flashlight.getScale().x<=0.2)
                m_flashlight.setScale(0,0);
        }
        else
            m_flashlight.setScale(last_pos-(float)abs(click.getPosition().x-player_pos.x)/200,last_pos-(float)abs(click.getPosition().x-player_pos.x)/200);
    }
    void addSource(const sf::Vector2f& position, const sf::Vector2f& size = sf::Vector2f(10,10),bool is_dynamic = false,int grow_distance = 10)
    {
        sources.emplace_back(new LightSource(position,size,is_dynamic,grow_distance));
    }
    void eraseSources()
    {
        for(int i = 0; i<sources.size(); i++)
        {
            delete sources[i];
            sources.erase(sources.begin()+i);
        }
    }
    static Flashlight& instance()
    {
        static Flashlight temp;
        return temp;
    }
private:
    sf::RenderTexture m_flashlightTexture;
    sf::RenderTexture m_layer;
    sf::Sprite m_flashlight;
    sf::Sprite m_sprite;
    sf::Vector2f m_pos;
    Click& click = Click::instance();
    static float darkness_level;
    float last_pos;
    std::vector<LightSource*>sources;
};
#endif // FLASHLIGHT_H
