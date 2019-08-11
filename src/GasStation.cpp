#include "GasStation.h"

GasStation::GasStation(int& scene)
:scene(scene),fire_check(5)
{
    gas.setTexture(*TextureManager::get("gas"));
    house.setTexture(*TextureManager::get("gas_house"));
    gas.setScale(4,4);
    house.setScale(3.5,3.5);
    gas.setPosition(0,1080-gas.getGlobalBounds().height);
    house.setPosition(1400,1080-house.getGlobalBounds().height-60);//1400
    sf::Sprite path;
    path.setTexture(*TextureManager::get("asphalt"));
    path.setScale(4,4);
    booth.setTexture(*TextureManager::get("booth"));
    booth.setScale(3.5,3.5);
    booth.setPosition(house.getPosition().x+house.getGlobalBounds().width-100,house.getPosition().y+house.getGlobalBounds().height-booth.getGlobalBounds().height-10);
    barrel.setTexture(*TextureManager::get("barrel"));
    barrel.setScale(4,4);
    barrel.setPosition(house.getPosition().x,house.getPosition().y+house.getGlobalBounds().height-barrel.getGlobalBounds().height);
    fire.setTexture(*TextureManager::get("fire_animation"));
    fire.setScale(4,4);
    fire.setPosition(barrel.getPosition().x+7,barrel.getPosition().y-barrel.getGlobalBounds().height+80);
    fire.setTextureRect(sf::IntRect(0,0,18,30));
    for(int i = 0; i<4; i++)
    {
        path.setPosition(i*path.getGlobalBounds().width,1080-path.getGlobalBounds().height);
        ground.push_back(path);
    }
    part.setSize(sf::Vector2f(5,5));
    crow.setTexture(*TextureManager::get("crow"));
    crow.setScale(2,2);
    crow.setPosition(house.getPosition().x+100,house.getPosition().y+45);

    items.add_item(barrel.getPosition(),barrel.getGlobalBounds(), "Hey, thats a really cool barrel, wish I could just take it.");
    car.setTexture(*TextureManager::get("car"));
    car.setScale(9,9);
    car.setPosition(20, 1080-car.getGlobalBounds().height+20);
    car.setTextureRect(sf::IntRect(0,0,80,60));
    forest.loadDefaultForest();
light.addSource(sf::Vector2f(barrel.getPosition().x+barrel.getGlobalBounds().width/2,barrel.getPosition().y-80),
                sf::Vector2f(9,9),true);
}

GasStation::~GasStation()
{
    //dtor
}

void GasStation::draw(sf::RenderWindow& window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        for(auto& part : ground)
        {
            part.move(player.speed,0);
        }
        gas.move(player.speed,0);
        house.move(player.speed,0);
        booth.move(player.speed,0);
        barrel.move(player.speed,0);
        fire.move(player.speed,0);
        for(int i = 0; i<particles.size(); i++)
            particles[i].move(player.speed,0);
        crow.move(player.speed,0);
        car.move(player.speed, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        for(auto& part : ground)
        {
            part.move(-player.speed,0);
        }
        gas.move(-player.speed,0);
        house.move(-player.speed,0);
        booth.move(-player.speed,0);
        barrel.move(-player.speed,0);
        fire.move(-player.speed,0);
        for(int i = 0; i<particles.size(); i++)
            particles[i].move(-player.speed,0);
        crow.move(-player.speed,0);
        car.move(-player.speed, 0);
    }
    fire_check.update();
        if(fire_check.getStatus())
        {
            fire.setTextureRect(sf::IntRect(sourcex*18,0,18,25));
            sourcex++;
            fire_check.restart();
        }
        if(sourcex == 4)
                sourcex = 0;
    for(auto& part : ground)
    {
        window.draw(part);
    }
    forest.draw(window);
    window.draw(gas);
    window.draw(house);
    window.draw(booth);
    window.draw(barrel);
    window.draw(crow);
    window.draw(car);
    //window.draw(fire);
    if(particles.size()<400)
    {
        if(rand()%2==0)
            part.setFillColor(sf::Color(116, 4, 4));
        else
            part.setFillColor(sf::Color(132, 44, 3));
        particles.push_back(part);
    }
    for(int i = 0; i<particles.size(); i++)
    {
        if(particles[i].getFillColor().a<5)
        {
            particles[i].setPosition(barrel.getPosition().x+rand()%70 + 5,barrel.getPosition().y+rand()%20);
            particles[i].setFillColor(sf::Color(particles[i].getFillColor().r,particles[i].getFillColor().g,particles[i].getFillColor().b,255));
        }
        else
        {
            particles[i].setFillColor(sf::Color(particles[i].getFillColor().r,particles[i].getFillColor().g,particles[i].getFillColor().b,particles[i].getFillColor().a-5));
            particles[i].move(-2+rand()%5,-2);
        }

        window.draw(particles[i]);
    }
    if(phone.getCamera().intersects(barrel.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        notes.add_note("Barrel","Hey, thats a really nice barrel. Warm");
        phone.turn_off_camera();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(barrel.getGlobalBounds().contains(Click::instance().getPosition()))
        {
            //dialog.say("Rusty, old barrel. Nothing spectacular. Its on fire though. Thats dangerous.");
            dialog.say("What idiot decided it was a good idea to have open fire on a gas station? Damn.");
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        scene = 1;
        Flashlight::instance().eraseSources();
    }
}
