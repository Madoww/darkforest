#include "InventorySystem.h"

int Item::posx = -100;
Item::Item(sf::Texture* item_tex, int itemtype)
:texture(item_tex)
{
    item.setTexture(*item_tex);
    item.setScale(8,8);
    item.setPosition(posx,-item.getGlobalBounds().height-23);
    default_position = sf::Vector2f(posx,0);
    posx+=item.getGlobalBounds().width+20;
    std::cout<<"POSX: "<<posx<<std::endl;
}
Item::~Item()
{

}
void Item::setPosition(const sf::Vector2f& position)
{
    item.setPosition(position);
}
void Item::draw(sf::RenderWindow& window)
{
    window.draw(item);
}
void Item::move(float x,float y)
{
    item.move(x,y);
}
void InventorySystem::open()
{
    is_open=true;
    std::cout<<"Inventory opened"<<std::endl;
}
void InventorySystem::close()
{
    is_open=false;
    std::cout<<"Inventory closed"<<std::endl;
}
void InventorySystem::draw(sf::RenderWindow& window)
{
    if(is_open)
    {
        for(auto& item:items)
        {
            if(background.getPosition().y<0)
            {
                item.move(0,4);
                background.move(0,4/items.size());
            }
            if(Click::instance().getGlobalBound().intersects(item.getGlobalBounds()))
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    item.setPosition(sf::Vector2f(Click::instance().getPosition().x-item.getGlobalBounds().width/2,
                                     Click::instance().getPosition().y-item.getGlobalBounds().height/2));
                    eq = item;
                }
                else
                {
                    item.setPosition(item.getDefaultPosition());
                    eq.setPosition(item.getPosition());
                }
            }
            else if(background.getPosition().y == 0)
            {
                item.setPosition(item.getDefaultPosition());
                eq.setPosition(item.getPosition());
            }
        }
    }
    else
    {
        for(auto& item:items)
        {
            if(background.getPosition().y>-background.getGlobalBounds().height)
            {
                item.move(0,-4);
                background.move(0,-4/(signed)items.size());
            }
        }
    }
    window.draw(background);
    for(auto& item : items)
    {
        item.draw(window);
    }
}
void InventorySystem::add_item(sf::Texture* item_tex, int itemtype)
{
    if(itemtype == type::single)
    {
        for(int i = 0; i<items.size(); i++)
        {
            if(items[i].getTexture()==item_tex)
                break;
            items.emplace_back(Item(item_tex,itemtype));
        }
        if(items.size()==0)
            items.emplace_back(Item(item_tex,itemtype));
    }
    if(itemtype == type::multi)
        items.emplace_back(Item(item_tex,itemtype));
}
void InventorySystem::remove_item(int number)
{
    Item::posx-=items[number].getGlobalBounds().width+20;
    items.erase(items.begin()+number);
}

InventorySystem::InventorySystem()
:eq(TextureManager::get("toolbox"),0)
{
    background.setSize(sf::Vector2f(1600,150));
    background.setPosition(sf::Vector2f(0,-150));
    background.setFillColor(sf::Color(111,111,111,20));
}

InventorySystem::~InventorySystem()
{
    //dtor
}
