#include "Forest2.hpp"
#include "Phone.h"

Forest2::Forest2(int& scene)
:scene(scene),cross_fire(sf::Vector2f(2000,700),250),church_stairs(6*5,5*5,5),inside_stairs(4*5,3*5,3,true)
{
    sf::Sprite temp;
    temp.setTexture(*TextureManager::get("grass"));
    temp.setScale(3,3);
    for(int i = -5; i<200; i++)
    {
        temp.setPosition(sf::Vector2f(i*64*3,950));
        grass.push_back(temp);
    }
    forest.loadDefaultForest();
    forest.add_position(0,85);
    forest.add_object(forest_object(sf::Vector2f(2000,0),5,TextureManager::get("booth")));
    forest.sort();
    ///player.setPosition(sf::Vector2f(player.getPosition().x+500+offset,1080-215));
    player.setPosition(sf::Vector2f(player.getPosition().x+offset,1080-195));
    bunker.setTexture(*TextureManager::get("bunker"));
    bunker.setScale(4.5,4.5);
    bunker.setPosition(1300+offset,840);
    //light.eraseSources();
    //light.setLevel(230);
    player.setRotation(Player::Rotation::Left);
    lamp.setTexture(*TextureManager::get("lamp"));
    lamp.setScale(5,5);
    lamp.setPosition(1450+offset,550);
    //light.addSource(sf::Vector2f(lamp.getPosition().x-offset,lamp.getPosition().y+400),sf::Vector2f(20,20));
    int x = 0;
    while(x<offset)
    {
        camera.move(1,0);
        x++;
    }
    cross.setTexture(*TextureManager::get("cross_big"));
    cross.setScale(4.8,4.8);
    cross.setPosition(2000,1080-cross.getGlobalBounds().height-50);
    cross_fire.setPosition(sf::Vector2f(cross.getPosition().x+80,cross.getPosition().y+cross.getGlobalBounds().height-30));
    cross2 = cross;
    cross2.setPosition(cross2.getPosition().x+900,cross2.getPosition().y);
    cross2.setScale(-cross2.getScale().x,cross2.getScale().y);
    //camera.zoom(2.7);
    //light.addSource(sf::Vector2f(2100,700),sf::Vector2f(20,20),true);

    Player::instance().setColor(sf::Color::White);
    house.setTexture(*TextureManager::get("village_house"));
    church.setTexture(*TextureManager::get("church"));
    house.setScale(5, 5);
    house.setPosition(0,1080-house.getGlobalBounds().height-60);
    church.setScale(5,5);
    church.setPosition(3200, 1080-church.getGlobalBounds().height-60);
    church_inside.setTexture(TextureManager::get("church_inside"));
    church_inside.setSize(sf::Vector2f(222*5,108*5));
    church_inside.setFillColor(sf::Color(255,255,255,0));
    sf::RectangleShape b;
    b.setFillColor(sf::Color(0,0,0,0));
    b.setSize(sf::Vector2f(1920,300));
    backs.push_back(b);
    backs.push_back(b);
    b.setSize(sf::Vector2f(600,1080));
    backs.push_back(b);
    backs.push_back(b);
    backs[0].setPosition(church.getPosition());
    backs[1].setPosition(church.getPosition().x,church.getPosition().y+church.getGlobalBounds().height);
    backs[2].setPosition(church.getPosition().x,church.getPosition().y);
    backs[3].setPosition(church.getPosition().x+church.getGlobalBounds().width-400,church.getPosition().y);
}

void Forest2::update()
{
    forest.update();
    cross_fire.update();
    church_inside.setPosition(sf::Vector2f(church.getPosition().x+45*5,church.getPosition().y+77*5));
    backs[0].setPosition(church.getPosition().x,church.getPosition().y+100);
    backs[1].setPosition(church.getPosition().x,church.getPosition().y+church.getGlobalBounds().height-200);
    backs[2].setPosition(church.getPosition().x-350,church.getPosition().y);
    backs[3].setPosition(church.getPosition().x+church.getGlobalBounds().width,church.getPosition().y);
    if(player.getPosition().x>church.getPosition().x+45*5 && church.getColor().a>0)
    {
        church.setColor(sf::Color(255,255,255,church.getColor().a-5));
        church_inside.setFillColor(sf::Color(255,255,255,church_inside.getFillColor().a+5));
        for(auto& b : backs)
            b.setFillColor(sf::Color(0,0,0,b.getFillColor().a+5));
        camera.zoom(0.994);
        camera.move(0.5,1);
    }
    if(player.block_movement == false){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        bunker.move(player.speed,0);
        lamp.move(player.speed+0.03,0);
        cross.move(player.speed,0);
        cross2.move(player.speed,0);
        house.move(player.speed,0);
        church.move(player.speed,0);
        //camera.move(1,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        bunker.move(-player.speed,0);
        lamp.move(-player.speed-0.03,0);
        cross.move(-player.speed,0);
        cross2.move(-player.speed,0);
        house.move(-player.speed,0);
        church.move(-player.speed,0);
        //camera.move(-1,0);
    }
    }
    if(struggle > 0)
    {
        if(ButtonPressed::buttonPressed(sf::Keyboard::Space))
        {
            struggle--;
        }
    }
    else if(captured==false)
        player.block_movement = false;
    if(grass[9].getPosition().x>2000 && struggle > 0) //3000
    {
        if(player.block_movement == false)
        {
            //Enemies::spawn(std::make_unique<Villager>(sf::Vector2f(3000,790)));
            //Enemies::spawn(std::make_unique<Villager>(sf::Vector2f(0,790)));
            Enemies::spawn(std::make_unique<Villager>(sf::Vector2f(3000,790)));
            Enemies::spawn(std::make_unique<Villager>(sf::Vector2f(0,790)));
            camera.slow_move(250,2);
        }
        player.block_movement = true;
    }
    for(int i = 0; i<Enemies::size(); i++)
    {
        if(Enemies::getGlobalBounds(i).contains(player.getPosition()))
        {
            forest.add_position(-500);
            bunker.setPosition(-500, bunker.getPosition().y);
            lamp.setPosition(-500,lamp.getPosition().y);
            for(auto& g : grass)
                g.move(-500,0);
            Enemies::kill_all();
            //camera.slow_move(2100,3);
            captured = true;
            player.block_movement = true;
            light.delete_source(0);
            light.addSource(sf::Vector2f(cross.getPosition().x,cross.getPosition().y+cross.getGlobalBounds().height-50),sf::Vector2f(20,20),true);
        }
    }
    if(captured)
    {
        forest.move_forest(-3);
        cross.move(-3,0);
        for(auto& g : grass)
            g.move(-3.5,0);
        light.move_sources(-3, 0);
        cross_fire.move(-3);
        cross2.move(-3,0);
        if(player.getPosition().x>cross.getPosition().x)
        {
            captured = false;
        }
    }
    /*stairs[0].setPosition(church.getPosition().x, church.getPosition().y+177*5);
    stairs[1].setPosition(church.getPosition().x+6*5,church.getPosition().y+173*5);
    stairs[2].setPosition(church.getPosition().x+13*5, church.getPosition().y+167*5);
    for(auto& stair : stairs)
    if(player.getPosition().x>stair.getPosition().x && player.getPosition().x<stair.getPosition().x+stair.getGlobalBounds().width && player.getPosition().y+120>stair.getPosition().y)
        player.setPosition(sf::Vector2f(player.getPosition().x,player.getPosition().y-stair.getGlobalBounds().height));*/
    church_stairs.update(sf::Vector2f(church.getPosition().x,church.getPosition().y+205*5));
    inside_stairs.update(sf::Vector2f(church_inside.getPosition().x+335*2.5,church_inside.getPosition().y+209*2.5));
}

void Forest2::draw(sf::RenderWindow& window)
{
    forest.draw(window);
    window.draw(lamp);
    window.draw(bunker);
    window.draw(cross);
    window.draw(cross2);
    window.draw(house);
    for(auto& b: backs)
        window.draw(b);
    window.draw(church_inside);
    window.draw(church);
    //inside_stairs.draw(window);
    //church_stairs.draw(window);
    cross_fire.draw(window);
}

void Forest2::draw_over(sf::RenderWindow& window)
{
    if(basic_zoom<11)
    {
        camera.zoom(0.99);
        Phone::instance().zoom_camera(0.98);
        basic_zoom++;
    }
    for(auto& g : grass)
    {
        if(player.block_movement == false){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            g.move(player.speed+0.5,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            g.move(-player.speed-0.5,0);
        }
        window.draw(g);
    }
}
