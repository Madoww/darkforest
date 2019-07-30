#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H
#include<SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ClickCheck.h"
#include <vector>

class Item
{
public:
    Item(sf::Texture* item_tex, int itemtype);
    ~Item();
    void move(float x, float y);
    inline const sf::Vector2f& getPosition(){return item.getPosition();}
    inline sf::FloatRect getGlobalBounds(){return item.getGlobalBounds();}
    inline sf::Texture* getTexture(){return texture;}
    inline sf::Vector2f getDefaultPosition(){return default_position;}
    void setPosition(const sf::Vector2f& position);
    void setScale(float scale){item.setScale(scale,scale);}
    float getScale(){return item.getScale().x;}
    void draw(sf::RenderWindow&);
    inline void setOrigin(const sf::Vector2f& origin){item.setOrigin(origin);}
    static int posx;
private:
    sf::Texture* texture;
    sf::Sprite item;
    sf::Vector2f default_position;
    int ID;
    
};

class InventorySystem
{
public:
    enum type
    {
        single = 0,
        multi
    };
    enum ID
    {
        toolbox = 0
    };
    virtual ~InventorySystem();
    InventorySystem(const InventorySystem&) = delete;
    InventorySystem operator=(const InventorySystem&) = delete;
    void add_item(sf::Texture* item_tex, int itemtype = 0);
    void remove_item(int number);
    void open(); void close();
    void draw(sf::RenderWindow&);
    inline static InventorySystem& instance()
    {
        static InventorySystem instance;
        return instance;
    }
    bool getStatus(){return is_open;}
    Item eq;
private:
    InventorySystem();
    std::vector<Item>items;
    bool is_open = false;
    sf::RectangleShape background;
};

#endif // INVENTORYSYSTEM_H
