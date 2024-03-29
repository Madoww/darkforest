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
    void setScale(float scale){m_player.setSize(sf::Vector2f(m_player.getSize().x-scale,m_player.getSize().y-scale));m_player.setOrigin(m_player.getSize().x/2,m_player.getSize().y/2);}
    sf::Vector2f getScale(){return m_player.getScale();}
    void move(float x);
    bool animated(){return is_animated;}
    bool is_animated = false;
    sf::Vector2f getPosition(){return m_player.getPosition();}
    void setPosition(const sf::Vector2f& position){m_player.setPosition(position);}
    void setColor(const sf::Color& color){m_player.setFillColor(color);}
    sf::RectangleShape* getPointer(){return &m_player;}
    const sf::Texture* getTexture(){return m_player.getTexture();}
    const sf::FloatRect& getGlobalBounds(){return m_player.getGlobalBounds();}
    inline static Player& instance()
    {
        static Player pp(sf::Vector2f(1600,900));
        return pp;
    }
    float speed;
    bool move_player = false;
    bool block_movement = false;
    void reset_animation(){sourcex = 0;m_player.setTextureRect(sf::IntRect(sourcex*64,0,64,64));}
    bool allow_stand = true;
    bool is_sitting = false;
    void quick_animate(const sf::Texture*,int);
    Check anim_check;
    enum Rotation
    {
        Left,
        Right
    };
    void setRotation(int rot){right = rot;}
virtual ~Player();
private:
    sf::RectangleShape m_player;
    float starting_scale = 4.5;
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
    const sf::Texture* anim_tex;
    int anim_lenght;
public:
    bool is_walking = false;
    bool do_crouch = false;
    bool do_sit = false;
    bool do_drop = false;
    bool falling = false;
    bool m_animated = false;
};

#endif // PLAYER_H
