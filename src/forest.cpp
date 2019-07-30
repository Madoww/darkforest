#include "forest.h"

forest_object::forest_object(const sf::Vector2f& position, float distance, sf::Texture* tex,const sf::Vector2f& window_size_ref)
{
    //srand(time(NULL));
        tree.setTexture(*tex);
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%2+1 == 1)
        {
            tree.setScale(3-distance/4,3);
        }
        else
        {
            tree.setScale(-3+distance/4,3);
            tree.setPosition(tree.getPosition().x+tree.getGlobalBounds().width,tree.getPosition().y);
        }
    }


    else
    {
        tree.setScale(3,3);
    }
    int color = rand()%40;
    tree.setColor(sf::Color(255-color,255-color,255-color));
    tree.setPosition(position.x-20,window_size_ref.y-tree.getGlobalBounds().height-distance*30-140);
    if(tex == TextureManager::get("tree"))
        tree.setPosition(tree.getPosition().x+100,tree.getPosition().y-20);
    tree.setColor(sf::Color(tree.getColor().r-distance*16,tree.getColor().g-distance*16,tree.getColor().b-distance*16));
    tree.setPosition(tree.getPosition().x-1000,tree.getPosition().y+200);
    if(tree.getTexture()==TextureManager::get("grass"))
        m_distance = distance;
    else
        m_distance = distance+(float)(rand()%20)/10;
    if(tex == TextureManager::get("tree"))
    {
        if(rand()%3==1)
            tree.setTexture(*TextureManager::get("tree2"));
        else
            tree.setTexture(*TextureManager::get("tree3"));
    }
    static sf::Vector2f window_size=window_size_ref;
}
void move(movable& object, bool right)
{
    if(right)
        object.move(-Player::instance().speed/object.m_distance*0.92,0);
    else
        object.move(Player::instance().speed/object.m_distance*0.92,0);
}

void forest_object::move(float x, float y)
{
    tree.move(x,y);
}
void Bush::move(float x, float y)
{
    bush.move(x,y);
}

void forest_object::draw(sf::RenderWindow& window)
{
    window.draw(tree);
}

Bush::Bush(int position, float distance)
{
    m_distance = distance;
    bush.setTexture(*TextureManager::get("bush"));
    bush.setPosition(sf::Vector2f(position,700));
}
void Bush::draw(sf::RenderWindow& window)
{
    window.draw(bush);
}

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
    for(int i = 1; i<161; i++)
    {
        objects.emplace_back(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+1,TextureManager::get("tree"),sf::Vector2f(1600,900)));
        objects.emplace_back(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+4,TextureManager::get("tree")));
        objects.emplace_back(forest_object(sf::Vector2f(i*50+(-40+rand()%80),0),rand()%3+7,TextureManager::get("tree")));
        bushes.emplace_back(Bush(i*250,1));
    }
    for(int i = 0; i<600; i++)
    {
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),0.92,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),2,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),3,TextureManager::get("grass")));
    }
    for(int i = 0; i<300; i++)
    {
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),4,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),5,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),6,TextureManager::get("grass")));
    }
    for(int i = 0; i<100; i++)
    {
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),7,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),8,TextureManager::get("grass")));
        objects.emplace_back(forest_object(sf::Vector2f(i*60+(-10+rand()%20),0),9,TextureManager::get("grass")));
    }
    grass.setTexture(*TextureManager::get("ground"));
    grass.setPosition(0,900-grass.getGlobalBounds().height-100);
    std::sort(std::begin(objects),std::end(objects));
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
    for(int i = 0; i<objects.size(); i++)
    {
        if(objects[i].is_tree() && objects[i].getPosition().x > house.getPosition().x && objects[i].getPosition().x < house.getPosition().x+house.getGlobalBounds().width && objects[i].getDistance()<=2)
        {
            objects.erase(objects.begin()+i);
        }
    }
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
    if(scene==1)
        window.draw(path);
    window.draw(grass);
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

    for(auto& object : objects)
    {
        if(!player.is_animated){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            move(object,true);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            move(object,false);}
        if(object.getGlobalBounds().intersects(drawArea.getGlobalBounds()))
            object.draw(window);
    }
    for(auto& bush : bushes)
    {
        if(!player.is_animated){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            move(bush,true);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            move(bush,false);}
        //bush.draw(window);
    }
    //window.draw(road);
    trunk_status.update();
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
    if(scene==1)
    {
       window.draw(car);
        window.draw(house);
        window.draw(roof);
    }

}
