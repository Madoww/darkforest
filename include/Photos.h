#ifndef Photos_h
#define Photos_h
#include <vector>
#include <SFML/Graphics.hpp>
#include "ClickCheck.h"
#include <fstream>

class Photo
{
 public:
     Photo(sf::Texture*);
    void draw(sf::RenderWindow&);
    void setPosition(const sf::Vector2f& pos){photo.setPosition(pos);}
    void setScale(float x, float y){photo.setScale(x,y);}
    void setAlpha(float a){photo.setColor(sf::Color(255,255,255,a));}
    sf::Vector2f getPosition(){return photo.getPosition();}
    const sf::FloatRect& getGlobalBounds(){return photo.getGlobalBounds();}
    sf::Texture* get_texture_ptr(){return tex;}
    float getAlpha(){return static_cast<float>(photo.getColor().a);}
    void move(float x, float y){photo.move(x,y);}
    int relative_pos;
 protected:
    sf::Texture* tex;
    sf::Sprite photo;
};

class Photos
{
public:
    inline static Photos& instance()
    {
        static Photos temp;
        return temp;
    }
    ~Photos();
    void update(const sf::Vector2f& position);
    void draw(sf::RenderWindow&);
    void setPosition(const sf::Vector2f&);
    void open_last_picture();
    void restart_check(){open_check.restart();}
    void add_photo(Photo&&);
    void scroll_up();
    void scroll_down();
    int screens_taken;
    const sf::Texture* getLastPic(){return photos[photos.size()-1].get_texture_ptr();}
private:
    Photos();
    sf::RectangleShape background;
    int ypos;
    int xpos;
    bool draw_main = false;
    std::vector<Photo>photos;
    sf::Sprite main_photo;
    Click& click = Click::instance();
    Check open_check;
    std::fstream file;
};

#endif /* Photos_h */
