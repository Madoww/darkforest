#include "Player.h"

Player::Player(const sf::Vector2f& window_size)
:animation_check(4),standup_check(10),crouch_check(5),sit_check(4), drop_check(4),anim_check(5)
{
    m_player.setTexture(TextureManager::get("player"));
    m_player.setSize(sf::Vector2f(48,48));
    m_player.setScale(starting_scale,starting_scale);
    m_player.setOrigin(24,24);
    m_player.setPosition(sf::Vector2f(window_size.x/2,window_size.y-m_player.getGlobalBounds().height+330));
    m_player.setTextureRect(sf::IntRect(0,0,48,48));
    this->window_size = window_size;
}

Player::~Player()
{
    //dtor
}
void Player::draw(sf::RenderWindow& window)
{
    if(!is_animated && !block_movement && !m_animated)
    {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        right = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        right = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || move_player)
    {
        animation_check.update();
        if(animation_check.getStatus())
        {
            m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            if(sourcex < animation_lenght)
            {
                sourcex++;
            }
            else
            {
                sourcex=0;
            }

            animation_check.restart();
        }
    }
    else if(!do_crouch && !do_sit && !block_movement)
    {
        m_player.setTextureRect(sf::IntRect(0,0,64,64));
        //sourcex = 0;
    }

    if(right)
    {
        if(m_player.getScale().x<starting_scale)
            m_player.setScale(m_player.getScale().x+1,m_player.getScale().y);
    }
    else
    {
        if(m_player.getScale().x>-starting_scale)
            m_player.setScale(m_player.getScale().x-1,m_player.getScale().y);
    }
    }
        //m_player.setScale(starting_scale,starting_scale);
    //if(do_crouch)
    crouch_animation();
    sit_animation();
    drop_animation();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && allow_stand)
    {
        do_crouch=false;
        do_sit = false;
    }
    if(m_animated)
    {
        block_movement = true;
        anim_check.update();
        if(anim_check.getStatus())
        {
            if(sourcex < anim_lenght-1)
            {
                sourcex++;
                m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            }
            anim_check.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            m_animated = false;
    }
    if(!m_animated && m_player.getTexture()==anim_tex)
    {
        anim_check.update();
        if(anim_check.getStatus())
        {
            if(sourcex >0)
            {
                sourcex--;
                m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            }
            else
            {
                block_movement = false;
                m_player.setTexture(TextureManager::get("player"));
            }
            
            anim_check.restart();
        }
    }
    if(!m_animated)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            quick_animate(TextureManager::get("crouch"), 6);
    }
    window.draw(m_player);
}

void Player::stand_up()
{
    do_sit = false;
    do_crouch = false;
}
void Player::crouch()
{
    m_player.setTexture(TextureManager::get("crouch"));
    sourcex=1;
    is_animated=true;
    do_crouch = true;
}
void Player::sit()
{
    m_player.setTexture(TextureManager::get("sit"));
    sourcex=1;
    is_animated=true;
    do_sit = true;
}
void Player::drop()
{
    m_player.setTexture(TextureManager::get("player_drop"));
    sourcex=1;
    is_animated=true;
    do_sit = false;
    is_sitting = false;
    do_drop = true;
}
void Player::crouch_animation()
{
    crouch_check.update();
    if(crouch_check.getStatus())
    {
        if(do_crouch)
        {
            animation_lenght=5;
            m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            if(sourcex < animation_lenght)
            {
                sourcex++;
            }
        }
        /*if(do_crouch==false && m_player.getTexture()==TextureManager::get("crouch"))
        {
            if(sourcex>0)
            {
                sourcex--;
                m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            }
            else
            {
                m_player.setTexture(TextureManager::get("player"));
                is_animated=false;
                animation_lenght=10;
            }
        }*/
        crouch_check.restart();
    }
}
void Player::sit_animation()
{
    sit_check.update();
    if(sit_check.getStatus())
    {
        if(do_sit)
        {
            animation_lenght=12;
            m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            if(sourcex < animation_lenght)
            {
                sourcex++;
                m_player.setPosition(m_player.getPosition().x,m_player.getPosition().y+6);
            }
            else
                is_sitting = true;
        }
        if(do_sit==false && m_player.getTexture()==TextureManager::get("sit"))
        {
            if(sourcex>0)
            {
                sourcex--;
                m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
                m_player.setPosition(m_player.getPosition().x,m_player.getPosition().y-6);
            }
            else
            {
                m_player.setTexture(TextureManager::get("player"));
                is_animated=false;
                animation_lenght=10;
            }
        }
        sit_check.restart();
    }
}
void Player::drop_animation()
{
    drop_check.update();
    if(drop_check.getStatus())
    {
        if(do_drop)
        {
            animation_lenght=21;
            m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
            if(sourcex < animation_lenght)
            {
                sourcex++;
            }
            else
            {
                sourcex = 0;
                do_drop = false;
                move_player = false;
                m_player.setTexture(TextureManager::get("player"));
                m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));
                is_animated = false;
                animation_lenght=10;
                falling = false;

            }
            if(sourcex <9)
                m_player.setPosition(m_player.getPosition().x+8,m_player.getPosition().y);
            else if(sourcex <16)
            {
                falling = true;
                m_player.setPosition(m_player.getPosition().x-2,m_player.getPosition().y+5);
            }

            if(sourcex >16)
                falling = false;
        }
        drop_check.restart();
    }
}

void Player::quick_animate(const sf::Texture* tex, int length)
{
    if(m_player.getTexture()!=tex)
        m_player.setTexture(tex);
    m_animated = true;
    anim_tex = tex;
    anim_lenght = length;
    sourcex = 0;
}
