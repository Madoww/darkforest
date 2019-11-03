#include "forest.h"


Forest::Forest(int& scene)
:trunk_open(10),scene(scene),trunk_status(100)
{
    srand(time(NULL));
    drawArea.setSize(sf::Vector2f(1920,1080));
    car.setTexture(*TextureManager::get("car"));
    house.setSize(sf::Vector2f(750,450));
    roof.setSize(sf::Vector2f(800,300));
    roof.setTexture(TextureManager::get("roof"));
    house.setTexture(TextureManager::get("house"));
    forest.loadDefaultForest();

    grass.setTexture(*TextureManager::get("ground"));
    grass.setPosition(0,900-grass.getGlobalBounds().height-100);
    forest.add_object(forest_object(sf::Vector2f(2000+(-10+rand()%20),-20),2,TextureManager::get("booth")));
    forest.sort();
    path.setSize(sf::Vector2f(8000,100));
    TextureManager::get("path")->setRepeated(true);
    path.setTexture(TextureManager::get("path"));
    path_tex.setRepeated(true);
    path.setTextureRect(sf::IntRect(0,0,path.getSize().x,100));
    path.setPosition(-1000,910);
    path.setScale(1,2);

    car.setScale(9,9);
    car.setPosition(0,900-car.getGlobalBounds().height+200);
    car.setTextureRect(sf::IntRect(0,0,80,60));

    house.setPosition(sf::Vector2f(1000,900-path.getGlobalBounds().height-house.getGlobalBounds().height+42+200));
    roof.setPosition(house.getPosition().x-20,house.getPosition().y-roof.getGlobalBounds().height+130);
    /*for(int i = 0; i<objects.size(); i++)
    {
        if(objects[i].is_tree() && objects[i].getPosition().x > house.getPosition().x && objects[i].getPosition().x < house.getPosition().x+house.getGlobalBounds().width && objects[i].getDistance()<=2)
        {
            objects.erase(objects.begin()+i);
        }
    }*/
    trunk.setSize(sf::Vector2f(60,200));
    trunk.setPosition(car.getPosition().x+100,car.getPosition().y+car.getGlobalBounds().height/2-80);
    door.setSize(sf::Vector2f(37*house.getSize().x/150,63*house.getSize().y/90));
    door.setPosition(house.getPosition().x+15*house.getSize().x/150,house.getPosition().y+24*house.getSize().y/90);
}

Forest::~Forest()
{
    //dtor
}
void Forest::draw(sf::RenderWindow& window)
{
    resetPosition();
    if(scene==1)
        window.draw(path);
    window.draw(grass);

    forest.draw(window);
    //window.draw(road);
    trunk_status.update();

    if(scene==1)
    {
       window.draw(car);
        window.draw(house);
        window.draw(roof);
    }

}
void Forest::update()
{
    forest.update();
    if(!player.is_animated && scene==1){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        path.move(Player::instance().speed,0);
        car.move(Player::instance().speed,0);
        house.move(Player::instance().speed,0);
        door.move(Player::instance().speed,0);
        roof.move(Player::instance().speed,0);
        trunk.move(Player::instance().speed,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        path.move(-Player::instance().speed,0);
        car.move(-Player::instance().speed,0);
        house.move(-Player::instance().speed,0);
        door.move(-Player::instance().speed,0);
        roof.move(-Player::instance().speed,0);
        trunk.move(-Player::instance().speed,0);
    }
    }
    if(trunk.getGlobalBounds().contains(Click::instance().getPosition()) && trunk_status.getStatus() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(trunkopen == false)
        {
            sourcex = 1;
            trunkopen = true;
        }

        else
            trunkopen = false;
        trunk_status.restart();
    }
    trunk_open.update();
    if(trunk_open.getStatus())
    {
        car.setTextureRect(sf::IntRect(sourcex*80,0,80,60));
        if(sourcex < 5 && trunkopen)
        {
            sourcex++;
        }
        if(sourcex > 0 && !trunkopen)
        {
            sourcex--;
        }
        if(sourcex==5)
            fullyopened = true;
        else
            fullyopened = false;
        trunk_open.restart();
    }
    if(fullyopened)
    {
        if(car.getGlobalBounds().contains(Click::instance().getPosition()))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                InventorySystem::instance().add_item(TextureManager::get("toolbox"),InventorySystem::type::single);
                InventorySystem::instance().open();
            }
        }
    }
    if(door.getGlobalBounds().contains(Click::instance().getPosition()))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            scene = 2;
            Player::instance().speed=2.5;
            Player::instance().setPosition(sf::Vector2f(Player::instance().getPosition().x,590));
        }
    }
    if(InventorySystem::instance().eq.getGlobalBounds().intersects(car.getGlobalBounds()) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Player::instance().crouch();
    }
}
void Forest::resetPosition()
{
    /*for(int i = 0; i<objects.size(); i++)
    {
        objects[i].setPosition(sf::Vector2f(objects[i].getPosition().x,objects[i].getDefaultPosition().y+105));
    }*/
}
