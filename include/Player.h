#ifndef PLAYER_H
#define PLAYER_H
#include "TextureManager.h"
#include "Phone.h"
#include "ClickCheck.h"

class Player
{
public:
    Player(const sf::Vector2f& window_size);
    void draw(sf::RenderWindow& window);
    void stand_up();
    void crouch();
    void sit();
    void drop();
    void crouch_animation();
    void sit_animation();
    void drop_animation();
    bool animated(){return is_animated;}
    bool is_animated = false;
    sf::Vector2f getPosition(){return m_player.getPosition();}
    void setPosition(const sf::Vector2f& position){m_player.setPosition(position);}
    sf::RectangleShape* getPointer(){return &m_player;}
    const sf::Texture* getTexture(){return m_player.getTexture();}
    const sf::FloatRect& getGlobalBounds(){return m_player.getGlobalBounds();}
    inline static Player& instance()
    {
        static Player pp(sf::Vector2f(1600,900));
        return pp;
    }
    float speed = 3;
    bool move_player = false;
    bool block_movement = false;
    void reset_animation(){sourcex = 0;m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));}
    bool allow_stand = true;
    bool is_sitting = false;
virtual ~Player();
private:
    sf::RectangleShape m_player;
    float starting_scale = 7;
    bool right = true;
    int sourcex = 1;
    int sourcey = 0;
    Check animation_check;
    Check standup_check;
    Check crouch_check;
    Check sit_check;
    Check drop_check;
    bool standup_animated = false;

    int animation_lenght = 10;
    sf::Vector2f window_size;
public:
    bool do_crouch = false;
    bool do_sit = false;
    bool do_drop = false;
    bool falling = false;
};

#endif // PLAYER_H
